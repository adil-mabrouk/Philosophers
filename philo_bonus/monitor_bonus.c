/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:10:46 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/07 18:12:38 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_args *args, t_philo *philo)
{
	if (get_time() - philo->last_meal_time > args->time_to_die)
	{
		args->dead = 1;
		printf("%zu %d died\n", get_time() - args->start, philo->id);
		return (1);
	}
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
			if (args->n_lim_meals <= args->philos[i].meals_counter)
			{
				args->all_meals_eaten++;
				if (args->all_meals_eaten >= args->philo_n)
				{
					args->full_flag = 1;
					return (NULL);
				}
			}
			if (is_dead(args, &args->philos[i]))
				return (NULL);
		}
	}
	return (NULL);
}
