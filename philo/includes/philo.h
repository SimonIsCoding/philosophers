/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/24 15:01:19 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//During the compilation, it might have a small delay of 1ms for every philos
//while they are doing they're actions.
//The more philos there are, the more delay will increase

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_MSG		"$>./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef enum states
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_states;

//The long variable is only to check if one philo is dead
//If yes, we change his value to 1 and everything is stopped.
//We need  mutex to change the value of this long variable. In that case, 
//only one philo would be able to change the value. And it will be changed once
//I couldn't put this structure in the t_philo struct because I wanted only one
//variable dead_flag. And not nb_philo's times dead_flag.
typedef struct big_brother_is_watching_u
{
	pthread_mutex_t	dead_mutex;
	long			dead_flag;
}	t_big;

//This is my main structure that contains everything. We put inside all the 
//argv that the user inputs
//We start counting in ms the life of our philo thanks to start_living variable
//And given that this is a struct timeval type, I used timestamp_in_ms to 
//convert it in ms
//We need a pointer for both forks to know where are the forks for each 
//philosophers
//And I also a muntex to print everything, otherwise I would have a lot of lines
//mixed together.
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

//ft_putnbr.c
void			ft_putnbr(int nb);

//write_msg.c
void			write_taken_fork_msg(t_philo *philo);
void			write_eat_msg(t_philo *philo);
void			write_sleep_msg(t_philo *philo);
void			write_think_msg(t_philo *philo);
void			write_dead_msg(t_philo *philo);

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
void			print(t_philo *philo, t_states philo_state);
//int			main(int argc, char **argv);

#endif