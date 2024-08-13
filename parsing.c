/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:56:28 by amabrouk          #+#    #+#             */
/*   Updated: 2024/08/12 16:27:18 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else if (*s == '-')
		exit_with_error("only positive values");
	if (!is_digit(*s))
		exit_with_error("Invalid input");
	num = s;
	while (*s++)
		len++;
	if (len > 10)
		exit_with_error("The vslue's too long");
	return (num);
}

size_t	ft_atol(char *s)
{
	size_t	number;

	number = 0;
	s = check_input(s);
	// printf("\nhere\n");
	while (is_digit(*s))
		number = number * 10 + *s++ - '0';
	if (number > INT_MAX)
		exit_with_error("The vslue's too long");
	return (number);
}

void	parse_input(t_args *args, char **av)
{
	args->philo_n = ft_atol(av[1]);
	args->time_to_die = ft_atol(av[2]) * 1e3;
	args->time_to_eat = ft_atol(av[3]) * 1e3;
	args->time_to_sleep = ft_atol(av[4]) *1e3;
	if (args->time_to_die < 6e4
		|| args->time_to_eat < 6e4
		|| args->time_to_sleep < 6e4)
		exit_with_error("use timestamps major than 60ms");
	if (av[5])
		args->n_lim_meals = ft_atol(av[5]);
	else
		args->n_lim_meals = -1;
}
