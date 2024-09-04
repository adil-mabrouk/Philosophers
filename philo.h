/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:12:55 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/05 00:42:42 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_args
{
	size_t			philo_n;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			n_lim_meals;
	size_t			all_meals_eaten;
	size_t			start;
	int				dead;
	int				full_flag;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	all_m_e;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitor_thread;
}			t_args;

typedef struct s_philo
{
	int				id;
	size_t			meals_counter;
	size_t			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_m;
	pthread_mutex_t	counter_mutex;
	t_args			*args;
}			t_philo;

void	parse_input(t_args *args, char **av);

void	*routine(void *arg);
void	*monitor(t_args *args);
int		ft_usleep(size_t milliseconds, t_args *args);
size_t	get_time(void);

int		error(char *str);

#endif