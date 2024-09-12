/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:32:27 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/13 00:47:33 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_args *args)
{
	size_t	i;

	sem_unlink("forks");
	sem_unlink("print_sem");
	sem_unlink("last_m_sem");
	args->forks = sem_open("forks", O_CREAT, 0644, args->philo_n);
	args->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	args->dead_sem = sem_open("last_m_sem", O_CREAT, 0644, 1);
	args->dead = 0;
	args->status = 0;
	i = -1;
	while (++i < args->philo_n)
	{
		args->philos[i].id = i + 1;
		args->philos[i].pid = -1;
		args->philos[i].meals_counter = 0;
		args->philos[i].args = args;
		args->start = get_time();
		sem_wait(args->last_m_sem);
		args->philos[i].last_meal_time = get_time();
		sem_post(args->last_m_sem);
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

		}
		else if (args->philos[i].pid < 0)
		{
			printf("Error: fork failed\n");
			return (1);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_args	*args;
	size_t	i;
	int	status;

	i = -1;
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
		while (++i < args->philo_n)
		{
			waitpid(-1, &status, 0);
			
			if (WEXITSTATUS(status))
			{
				
				i = -1;
				while (++i < args->philo_n)
					kill(args->philos[i].pid, SIGKILL);
				break ;
			}
		}
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_unlink("forks");
		sem_unlink("print_sem");
		free(args->philos);
		free(args);
	}
	else
		error("wrong number of arguments");
	return (0);
}
