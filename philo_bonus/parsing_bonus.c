/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:56:28 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/13 16:03:48 by amabrouk         ###   ########.fr       */
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

char	*check_input(char *s)
{
	char	*num;
	int		len;

	len = 0;
	while (is_space(*s))
		s++;
	if (*s == '+')
		s++;
	if (*s && !is_digit(*s))
	{
		printf("Invalid input\n");
		return (NULL);
	}
	num = s;
	while (*s++)
		len++;
	if (len > 10)
		error("The value's too long");
	return (num);
}

size_t	ft_atol(char *s)
{
	size_t	number;

	number = 0;
	s = check_input(s);
	if (!s)
		return (0);
	while (*s && is_digit(*s))
		number = number * 10 + *s++ - '0';
	if (*s && !is_digit(*s))
	{
		printf("Invalid input\n");
		return (0);
	}
	if (number > INT_MAX)
		error("The value's too long");
	return (number);
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
