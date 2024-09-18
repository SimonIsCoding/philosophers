/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/18 19:29:10 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_MSG		"$>./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct big_brother_is_watching_u
{
	pthread_mutex_t	dead_mutex;
	long			dead_flag;
}	t_big;

typedef struct philo
{
	long			thread_id;
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	long			eating_times;
	struct timeval	start_living;
	struct timeval	time_last_meal;
	long			timestamp_in_ms;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	print_mutex;
	t_big			*watcher;
}	t_philo;

//utils_functions.c
int				ft_isdigit(int c);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);

//parsing.c
int				check_error(int argc, char **argv);

//custom_usleep.c
void			precise_usleep(long usec);
long			timestamp_in_ms(struct timeval start);

//init.c
t_philo			*init_philo_struct(char **argv, t_big *watch);
int				init_threads(t_philo *philo);
pthread_mutex_t	*init_forks(t_philo *philo);
//void			print_philo(t_philo *philo);

//philo_routine.c
void			*philo_routine(void *arg);

//philo_routine_breaker.c
int				checking_death(t_philo *philo);
int				break_conditions(t_philo *philo);

//main.c
//int			main(int argc, char **argv);

#endif