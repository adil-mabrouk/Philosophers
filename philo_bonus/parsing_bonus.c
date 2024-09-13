/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:56:28 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/13 21:24:31 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*check_input(char *str)
{
	char	*tmp;

	tmp = str;
	while (is_space(*tmp))
		tmp++;
	if (*tmp == '+')
		tmp++;
	while (*tmp && is_digit(*tmp))
		tmp++;
	while (*tmp)
	{
		if (!is_space(*tmp))
			return (NULL);
		tmp++;
	}
	if (!*tmp)
		return (str);
	return (NULL);
}

size_t	ft_atol(char *str)
{
	size_t	result;

	result = 0;
	if (!check_input(str))
	{
		printf("Error: Invalid argument\n");
		return (0);
	}
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (str && is_digit(*str))
	{
		result = result * 10 + *str - '0';
		if (result > INT_MAX)
		{
			printf("Error: Argument out of range\n");
			return (0);
		}
		str++;
	}
	return (result);
}

void	parse_input(t_args *args, char **av)
{
	args->philo_n = ft_atol(av[1]);
	args->time_to_die = ft_atol(av[2]);
	args->time_to_eat = ft_atol(av[3]);
	args->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		args->n_lim_meals = ft_atol(av[5]);
	else
		args->n_lim_meals = -1;
}
