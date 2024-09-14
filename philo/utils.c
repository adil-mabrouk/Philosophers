/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:25:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/14 14:49:24 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_args *args)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&args->dead_mutex);
		if (args->dead == 1)
			return (pthread_mutex_unlock(&args->dead_mutex), 0);
		pthread_mutex_unlock(&args->dead_mutex);
		usleep(500);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	tiny_check(t_args args)
{
	if (args.philo_n == 0 || args.time_to_die == 0
		|| args.time_to_eat == 0 || args.time_to_sleep == 0
		|| args.n_lim_meals == 0)
		return (1);
	return (0);
}
