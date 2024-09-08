/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:24:35 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/08 21:33:17 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_take_forks(t_args *args, t_philo *philo)
{
	printf("here\n, %zu\n", args->philo_n);
	if (args->philo_n > 1)
		sem_wait(args->forks);
	if (args->dead == 1)
		return (sem_post(args->forks), 0);
	printf("%zu %d has taken a fork\n",
		get_time() - args->start, philo->id);
	if (args->philo_n == 1)
		args->dead = 1;
	sem_wait(args->forks);
	if (args->dead == 1)
		return (sem_post(args->forks), 0);
	printf("%zu %d has taken a fork\n", get_time() - args->start, philo->id);
	return (1);
}

int	is_eating(t_args *args, t_philo *philo)
{
	args->philos[philo->id - 1].last_meal_time = get_time();
	if (args->dead == 1)
		return (sem_post(args->forks), 0);
	printf("%zu %d is eating\n", get_time() - args->start, philo->id);
	ft_usleep(args->time_to_eat, args);
	philo->meals_counter++;
	if (args->full_flag == 1)
		return (args->dead = 1, 0);
	return (1);
}

int	is_sleeping(t_args *args, t_philo *philo)
{
	if (args->dead == 1)
		return (0);
	printf("%zu %d is sleeping\n", get_time() - args->start, philo->id);
	ft_usleep(args->time_to_sleep, args);
	return (1);
}

int	is_thinking(t_args *args, t_philo *philo)
{
	if (args->dead == 1)
		return (0);
	printf("%zu %d is thinking\n", get_time() - args->start, philo->id);
	return (1);
}

void	routine(t_args *args, t_philo *philo)
{
	// if (philo->id % 2 != 0)
	// 	ft_usleep(args->time_to_eat / 2, args);
	pthread_create(&args->monitor_thread, NULL, (void *)monitor, args);
	pthread_detach(args->monitor_thread);
	while (1)
	{
		if (!is_take_forks(args, philo))
			exit(args->dead);
		if (!is_eating(args, philo))
			exit(args->dead);
		if (!is_sleeping(args, philo))
			exit(args->dead);
		if (!is_thinking(args, philo))
			exit(args->dead);
		return ;
	}
	return ;
}
