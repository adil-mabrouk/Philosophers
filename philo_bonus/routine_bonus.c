/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:24:35 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/11 16:57:48 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_take_forks(t_args *args, t_philo *philo)
{
	if (args->philo_n > 1)
		sem_wait(args->forks);
	if (args->dead == 1)
		return (sem_post(args->forks), 0);
	sem_wait(args->print_sem);
	printf("%zu %d has taken a fork\n",
		get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	if (args->philo_n == 1)
		args->dead = 1;
	sem_wait(args->forks);
	if (args->dead == 1)
		return (sem_post(args->forks), sem_post(args->forks), 0);
	sem_wait(args->print_sem);
	printf("%zu %d has taken a fork\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	return (1);
}

int	is_eating(t_args *args, t_philo *philo)
{
	if (args->dead == 1)
		return (sem_post(args->forks), sem_post(args->forks), 0);
	sem_wait(args->print_sem);
	printf("%zu %d is eating\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	ft_usleep(args->time_to_eat, args);
	sem_post(args->forks);
	sem_post(args->forks);
	philo->meals_counter++;
	philo->last_meal_time = get_time();
	return (1);
}

int	is_sleeping(t_args *args, t_philo *philo)
{
	if (args->dead == 1)
		return (0);
	sem_wait(args->print_sem);
	printf("%zu %d is sleeping\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	ft_usleep(args->time_to_sleep, args);
	return (1);
}

int	is_thinking(t_args *args, t_philo *philo)
{
	if (args->dead == 1)
		return (0);
	sem_wait(args->print_sem);
	printf("%zu %d is thinking\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	return (1);
}

void	routine(t_args *args, t_philo *philo)
{
	args->index = philo->id - 1;
	pthread_create(&args->monitor_thread, NULL, (void *)monitor, args);
	pthread_detach(args->monitor_thread);
	if (philo->id % 2 == 0)
		ft_usleep(args->time_to_eat, args);
	while (1)
	{
		if (!is_take_forks(args, philo))
			break ;
		if (!is_eating(args, philo))
			break ;
		if (!is_sleeping(args, philo))
			break ;
		if (!is_thinking(args, philo))
			break ;
	}
	exit(0);
}
