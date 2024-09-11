/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:12:55 by amabrouk          #+#    #+#             */
/*   Updated: 2024/09/11 16:51:39 by amabrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo	t_philo;

typedef struct s_args
{
	size_t			philo_n;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			n_lim_meals;
	size_t			start;
	int				dead;
	int				status;
	int				full_flag;
	sem_t			*forks;
	t_philo			*philos;
	int				index;
	sem_t			*print_sem;
	pthread_t		monitor_thread;
}			t_args;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	size_t			meals_counter;
	size_t			last_meal_time;
	t_args			*args;
}			t_philo;

void	parse_input(t_args *args, char **av);

void	routine(t_args *arg, t_philo *philo);
void	*monitor(void *argss);
int		ft_usleep(size_t milliseconds, t_args *args);
size_t	get_time(void);

int		error(char *str);

#endif