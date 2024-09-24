/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:24:35 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/13 23:04:26 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_take_forks(t_args *args, t_philo *philo)
{
	sem_wait(args->forks);
	sem_wait(args->print_sem);
	printf("%zu %d has taken a fork\n",
		get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	sem_wait(args->forks);
	sem_wait(args->print_sem);
	printf("%zu %d has taken a fork\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	return (1);
}

int	is_eating(t_args *args, t_philo *philo)
{
	sem_wait(args->print_sem);
	printf("%zu %d is eating\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	sem_wait(args->last_m_sem);
	philo->last_meal_time = get_time();
	sem_post(args->last_m_sem);
	ft_usleep(args->time_to_eat);
	sem_post(args->forks);
	sem_post(args->forks);
	sem_wait(args->counter_sem);
	philo->meals_counter++;
	sem_post(args->counter_sem);
	return (1);
}

int	is_sleeping(t_args *args, t_philo *philo)
{
	sem_wait(args->print_sem);
	printf("%zu %d is sleeping\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	ft_usleep(args->time_to_sleep);
	return (1);
}

int	is_thinking(t_args *args, t_philo *philo)
{
	sem_wait(args->print_sem);
	printf("%zu %d is thinking\n", get_time() - args->start, philo->id);
	sem_post(args->print_sem);
	return (1);
}

void	*routine(t_args *args, t_philo *philo)
{
	args->index = philo->id - 1;
	if (pthread_create(&args->monitor_thread, NULL,
			(void *)monitor, args) == -1)
		exit(1);
	if (pthread_detach(args->monitor_thread) == -1)
		exit(1);
	if (philo->id % 2 == 0)
		usleep(100);
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
