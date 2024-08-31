/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:32:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/08/31 02:24:27 by amabrouk         ###   ########.fr       */
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

int	ft_usleep(size_t milliseconds, t_args args)
{
	size_t	start;

	if (args.dead == 1)
		return (0);
	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*monitor(t_args *args)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < args->philo_n)
		{
			// if (args->n_lim_meals <= args->philos[i].meals_counter)
			// 	return ;
			pthread_mutex_lock(&args->philos[i].last_m);
			if (get_time() - args->philos[i].last_meal_time >= args->time_to_die)
			{
				pthread_mutex_lock(&args->print_mutex);
				printf("%zu %d died\n", get_time() - args->start_time, args->philos[i].id);
				pthread_mutex_unlock(&args->print_mutex);
				pthread_mutex_lock(&args->dead_mutex);
				args->dead = 1;
				pthread_mutex_unlock(&args->dead_mutex);
				pthread_mutex_unlock(&args->philos[i].last_m);
				return (NULL);
			}
			pthread_mutex_unlock(&args->philos[i].last_m);
		}
	}
	return (NULL);
}

void	*dead_quit(t_args *args, t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&args->dead_mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)arg;
	args = philo->args;
	if (philo->id % 2 != 0)
		ft_usleep(args->time_to_eat / 2, *args);
	while (1)
	{
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d has taken a fork\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d has taken a fork\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is eating\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		ft_usleep(args->time_to_eat, *args);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&args->philos[philo->id - 1].last_m);
		args->philos[philo->id - 1].last_meal_time = get_time();
		pthread_mutex_unlock(&args->philos[philo->id - 1].last_m);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is sleeping\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		ft_usleep(args->time_to_sleep, *args);
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (dead_quit(args, philo));
		pthread_mutex_unlock(&args->dead_mutex);
		pthread_mutex_lock(&args->print_mutex);
		printf("%zu %d is thinking\n", get_time() - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args	*args;
	size_t	i;

	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
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
		pthread_mutex_init(&args->dead_mutex, NULL);
		pthread_mutex_init(&args->philos->last_m, NULL);
		pthread_mutex_init(&args->philos->counter_mutex, NULL);
		args->start_time = get_time();
		args->dead = 0;
		i = -1;
		while (++i < args->philo_n)
		{
			args->philos[i].id = i + 1;
			args->philos[i].meals_counter = 0;
			args->philos[i].last_meal_time = get_time();
			args->philos[i].right_fork = &args->forks[i];
			args->philos[i].left_fork = &args->forks[(i + 1) % args->philo_n];
			args->philos[i].args = args;
			pthread_mutex_init(&args->philos[i].last_m, NULL);
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
		if (pthread_create(&args->monitor_thread, NULL, (void *)monitor, args))
			return (1);
		while (++i < args->philo_n)
		{
			if (pthread_join(args->philos[i].thread_id, NULL))
				return (1);
		}
		if (pthread_join(args->monitor_thread, NULL))
			return (1);
		i = -1;
		while (++i < args->philo_n)
		{
			pthread_mutex_destroy(&args->forks[i]);
			pthread_mutex_destroy(&args->philos[i].last_m);
		}
		pthread_mutex_destroy(&args->print_mutex);
		pthread_mutex_destroy(&args->dead_mutex);
		pthread_mutex_destroy(&args->philos->counter_mutex);
		free(args->forks);
		free(args->philos);
		free(args);
	}
	else
		exit_with_error("wrong number of arguments");
	return (0);
}
