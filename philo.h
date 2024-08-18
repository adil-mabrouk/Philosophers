/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:12:55 by amabrouk          #+#    #+#             */
/*   Updated: 2024/08/17 17:41:06 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>

typedef	struct s_philo t_philo;

typedef struct s_args
{
	size_t			philo_n;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			n_lim_meals;
	size_t			last_meal_t;
	size_t			start_time;
	int				dead;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
}			t_args;


typedef	struct s_philo
{
    int				id;
    size_t			meals_counter;
	size_t			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args		*args;
}			t_philo;

// Parsing
void	parse_input(t_args *args, char **av);

// util functions
int		exit_with_error(char *str);

#endif