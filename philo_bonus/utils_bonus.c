/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:25:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/07 19:47:49 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(size_t milliseconds, t_args *args)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if (args->dead == 1)
			return (0);
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

int	error(char *str)
{
	printf("%s\n", str);
	return (1);
}
