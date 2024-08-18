/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:32:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/08/18 04:13:54 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	monitor(t_args *args)
{
	size_t	i = 0;
	size_t	t;

	t = get_time();
	while (1)
	{
		if (t - args->last_meal_t > args->time_to_die)
			break ;
		if (i == args->philo_n)
		{
			i = 0;
			t = get_time();
		}
		if (args->philos[i].meals_counter == args->n_lim_meals)
			break ;
		i++;
	}
	pthread_mutex_lock(&args->print_mutex);
	printf("%zu %lu died\n", get_time() - args->start_time, i + 1);
	pthread_mutex_unlock(&args->print_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)arg;
	args = philo->args;
	//
	if (philo->id % 2 == 0)
		ft_usleep(args->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%zu %d has taken a fork\n", get_time() - args->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%zu %d has taken a fork\n", get_time() - args->start_time, philo->id);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is eating\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex); 
		ft_usleep(args->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is sleeping\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		ft_usleep(args->time_to_sleep);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is thinking\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args	*args;
	size_t	i;

	args = malloc(sizeof(t_args));
	if (ac == 5 || ac == 6)
	{
		parse_input(args, av);
		args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_n);
		if (!args->forks)
			return (1);
		args->philos = malloc(sizeof(t_philo) * args->philo_n);
		if (!args->philos)
			return (1);
		pthread_mutex_init(&args->print_mutex, NULL);
		args->start_time = get_time();
		i = -1;
		while (++i < args->philo_n)
		{
			args->philos[i].id = i + 1;
			args->philos[i].meals_counter = 0;
			args->philos[i].right_fork = &args->forks[i];
			args->philos[i].left_fork = &args->forks[(i + 1) % args->philo_n];
			args->philos[i].args = args;
		}
		i = -1;
		while (++i < args->philo_n)
		{
			if (pthread_mutex_init(&args->forks[i], NULL))
				return (1);
		}
		i = -1;
		while (++i < args->philo_n)
		{
			if (pthread_create(&args->philos[i].thread_id, NULL, &routine, &args->philos[i]))
				return (1);
		}
		
		i = -1;
		while (++i < args->philo_n)
		{
			if (pthread_join(args->philos[i].thread_id, NULL))
				return (1);
		}
	}
	else
		exit_with_error("wrong number of arguments");
}  