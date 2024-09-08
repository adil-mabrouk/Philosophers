/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:32:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/08 21:35:36 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_args *args)
{
	size_t	i;

	sem_unlink("forks");
	sem_unlink("dead_sem");
	sem_unlink("print_sem");
	args->forks = sem_open("forks", O_CREAT, 0644, 1);
	args->dead_sem = sem_open("dead_sem", O_CREAT, 0644, 1);
	args->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	args->start = get_time();
	args->dead = 0;
	args->full_flag = 0;
	args->all_meals_eaten = 0;
	args->print_sem = NULL;
	args->dead_sem = NULL;
	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].id = i + 1;
		args->philos[i].pid = -1;
		args->philos[i].meals_counter = 0;
		args->philos[i].last_meal_time = get_time();
		args->philos[i].args = args;
	}
}

int	create_processes(t_args *args)
{
	size_t	i;

	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
		{
			routine(args, &args->philos[i]);
			exit (0);
		}
	}
	return (1);
}

void	destroy_and_free(t_args *args)
{
	size_t	i;

	i = -1;
	// while (++i < args->philo_n)
	// {
	// 	pthread_mutex_destroy(&args->forks[i]);
	// }
	free(args->forks);
	free(args->philos);
	free(args);
}

int	main(int ac, char **av)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (ac == 5 || ac == 6)
	{
		parse_input(args, av);
		args->forks = malloc(sizeof(sem_t) * args->philo_n);
		if (!args->forks)
			return (1);
		args->philos = malloc(sizeof(t_philo) * args->philo_n);
		if (!args->philos)
			return (1);
		data_init(args);
		if (!create_processes(args))
			return (1);
		// destroy_and_free(args);
	}
	else
		error("wrong number of arguments");
	return (0);
}
