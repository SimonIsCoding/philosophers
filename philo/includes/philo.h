/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/06 15:55:00 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MALLOC_ERROR	3
# define ERROR_MSG		"$>./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

//COLORS
# define BOLD_RED "\033[1;31m"
# define RESET	"\033[0m"

typedef struct philo
{
	int				thread_id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	//int				fork_remaining;
	struct timeval	start_living;
	struct timeval	time_last_meal;
	long			timestamp_in_ms;
	int				dead_flag;
//	t_mutex			mutex;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	print_mutex;
}				t_philo;

/*typedef struct mutex
{
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}				t_mutex;*/


//utils_functions.c
int			ft_isdigit(int c);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);


//parsing.c
int		check_error(int argc, char **argv);

//custom_usleep.c
long	get_elapsed_time_microseconds(struct timeval start,
						struct timeval end);
void	precise_usleep(long usec);
long	timestamp_in_ms(struct timeval start);

//philo_states.c
void	dying_state_for_one_philo(t_philo *philo);

//main.c

//init_philo_struct.c
t_philo	*init_philo_struct(char **argv);//to free once used
void	print_philo(t_philo *philo);

//philo_routine.c
void 	*philo_routine(void *arg);


# endif