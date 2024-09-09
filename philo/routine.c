/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:24:35 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/09 17:35:45 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_take_forks(t_args *args, t_philo *philo)
{
	if (args->philo_n > 1)
		pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead == 1)
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(&args->print_mutex),
			pthread_mutex_unlock(&args->dead_mutex), 0);
	printf("%zu %d has taken a fork\n",
		get_time() - args->start, philo->id);
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_unlock(&args->print_mutex);
	if (args->philo_n == 1)
		args->dead = 1;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead == 1)
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(&args->print_mutex),
			pthread_mutex_unlock(&args->dead_mutex), 0);
	printf("%zu %d has taken a fork\n", get_time() - args->start, philo->id);
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_unlock(&args->print_mutex);
	return (1);
}

int	is_eating(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->philos[philo->id - 1].last_m);
	args->philos[philo->id - 1].last_meal_time = get_time();
	pthread_mutex_unlock(&args->philos[philo->id - 1].last_m);
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead == 1)
		return (pthread_mutex_unlock(&args->print_mutex),
			pthread_mutex_unlock(&args->dead_mutex),
			pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	printf("%zu %d is eating\n", get_time() - args->start, philo->id);
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_unlock(&args->print_mutex);
	ft_usleep(args->time_to_eat, args);
	pthread_mutex_lock(&philo->counter_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->counter_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&args->full_mutex);
	if (args->full_flag == 1)
		return (pthread_mutex_unlock(&args->full_mutex), 0);
	pthread_mutex_unlock(&args->full_mutex);
	return (1);
}

int	is_sleeping(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead == 1)
		return (pthread_mutex_unlock(&args->print_mutex),
			pthread_mutex_unlock(&args->dead_mutex), 0);
	printf("%zu %d is sleeping\n", get_time() - args->start, philo->id);
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_unlock(&args->print_mutex);
	ft_usleep(args->time_to_sleep, args);
	return (1);
}

int	is_thinking(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if (args->dead == 1)
		return (pthread_mutex_unlock(&args->print_mutex),
			pthread_mutex_unlock(&args->dead_mutex), 0);
	printf("%zu %d is thinking\n", get_time() - args->start, philo->id);
	pthread_mutex_unlock(&args->dead_mutex);
	pthread_mutex_unlock(&args->print_mutex);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)arg;
	args = philo->args;
	if (philo->id % 2 != 0)
		ft_usleep(args->time_to_eat / 2, args);
	while (1)
	{
		if (!is_take_forks(args, philo))
			return (NULL);
		if (!is_eating(args, philo))
			return (NULL);
		if (!is_sleeping(args, philo))
			return (NULL);
		if (!is_thinking(args, philo))
			return (NULL);
	}
	return (NULL);
}
