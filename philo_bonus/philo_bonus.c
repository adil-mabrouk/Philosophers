/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:32:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/11 17:00:34 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_args *args)
{
	size_t	i;

	sem_unlink("forks");
	sem_unlink("print_sem");
	args->forks = sem_open("forks", O_CREAT, 0644, args->philo_n);
	args->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	args->dead = 0;
	args->status = 0;
	args->print_sem = NULL;
	args->forks = NULL;
	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].id = i + 1;
		args->philos[i].pid = -1;
		args->philos[i].meals_counter = 0;
		args->philos[i].args = args;
	}
}

int	create_processes(t_args *args)
{
	size_t	i;

	i = -1;
	args->start = get_time();
	while (++i < args->philo_n)
	{
		args->philos[i].last_meal_time = get_time();
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
		{
			routine(args, &args->philos[i]);
			exit (0);
		}
		else if (args->philos[i].pid < 0)
			exit(1);
	}
	return (1);
}

void	close_all(t_args *args)
{
	size_t	i;

	i = -1;
	while (++i < args->philo_n)
		kill(args->philos[i].pid, SIGKILL);
	sem_close(args->forks);
	sem_close(args->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
}

int	main(int ac, char **av)
{
	t_args	*args;
	size_t		i;

	i = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (ac == 5 || ac == 6)
	{
		parse_input(args, av);
		args->philos = malloc(sizeof(t_philo) * args->philo_n);
		if (!args->philos)
			return (1);
		data_init(args);
		if (!create_processes(args))
			return (1);
		while (i < args->philo_n)
		{
			waitpid(-1, &args->status, 0);
			if (args->status)
				close_all(args);
			i++;
		}
		free(args->philos);
		free(args);
	}
	else
		error("wrong number of arguments");
	return (0);
}
