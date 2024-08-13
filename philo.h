/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:12:55 by amabrouk          #+#    #+#             */
/*   Updated: 2024/08/12 10:42:10 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>

typedef	struct s_philo t_philo;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}			t_fork;

typedef struct s_args
{
	size_t	philo_n;
	size_t	time_to_die;
	size_t	time_to_sleep;
	size_t	time_to_eat;
	size_t	n_lim_meals;
	size_t	start_time;
	int		end_time;
	t_fork	*forks;					// array of forks
	t_philo	*philos;				// array of philos
}			t_args;


typedef	struct s_philo
{
    int			id;
    size_t		meals_counter;
	size_t		last_meal_time;
	int			dead;
	pthread_t	thread_id;
	t_fork		left_fork;
	t_fork		right_fork;
	t_args		*args;
}			t_philo;

// Parsing
void	parse_input(t_args *args, char **av);

// util functions
void	exit_with_error(char *str);