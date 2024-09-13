/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:10:46 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/13 16:48:43 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_args *args, t_philo *philo)
{
	sem_wait(args->last_m_sem);
	if (get_time() - philo->last_meal_time > args->time_to_die)
	{
		sem_post(args->last_m_sem);
		args->dead = 1;
		sem_wait(args->print_sem);
		printf("%zu %d died\n", get_time() - args->start, philo->id);
		exit(1);
	}
	sem_post(args->last_m_sem);
	return (0);
}

void	*monitor(void *argss)
{
	t_args	*args;

	args = (t_args *)argss;
	while (1)
	{
		if (args->philos[args->index].meals_counter >= args->n_lim_meals)
			exit(0);
		if (is_dead(args, args->philos + args->index))
			exit(1);
	}
	return (NULL);
}
