/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/18 16:10:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	checking_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->watcher->dead_mutex);
	if (philo->watcher->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->watcher->dead_mutex);
	return (0);
}

static int	break_conditions(t_philo *philo)
{
	//printf("entered in break_conditions\n");
//	printf("in break conditions *philo->watcher->dead_mutex = %p\n", &philo->watcher->dead_mutex);
//	printf("in break conditions *philo->watcher->dead_mutex = %li\n", philo->watcher->dead_mutex);
	if (checking_death(philo) == 1)
	{
//		printf("philo->thread_id = %li\n", philo->thread_id);
//		printf("checking_death = 1\n");
		return (1);
	}
	if (philo->nb_must_eat != -1 && philo->eating_times >= philo->nb_must_eat)
	{
//		printf("checking_death = 1\n");
		return (1);
	}
	if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
//		printf("checking_death = 1\n");
		pthread_mutex_lock(&philo->watcher->dead_mutex);
		philo->watcher->dead_flag = 1L;
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;214m%li %li is dead\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
//	printf("checking_death = 0\n");
	return (0);
}

static void	pick_correct_fork(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

static void	eat(t_philo *philo)
{
	struct timeval	reset;

	if (checking_death(philo) == 1)
		return ;
	pick_correct_fork(philo);
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;196m%li %li has taken a fork\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;93m%li %li is eating\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	precise_usleep(philo->time_to_eat * 1000);
	philo->eating_times++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->print_mutex);
//	printf("fin comer thread nb %li\n", philo->thread_id);
}

static void	philo_sleep(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;46m%li %li is sleeping\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->print_mutex);
//	printf("fin sleep thread nb %li\n", philo->thread_id);
}

static void	think(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	if (philo->nb_philo % 2 == 0 && philo->time_to_eat > philo->time_to_sleep)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;21m%li %li is thinking\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		precise_usleep((philo->time_to_eat - philo->time_to_sleep) * 1000);
		pthread_mutex_unlock(&philo->print_mutex);
	}
	if (philo->nb_philo % 2 == 1)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;21m%li %li is thinking\033[0m\n",
			timestamp_in_ms(philo->start_living), philo->thread_id);
		precise_usleep((philo->time_to_eat * 2 - philo->time_to_sleep) * 1000);
		pthread_mutex_unlock(&philo->print_mutex);
	}
//	printf("fin thinking thread nb %li\n", philo->thread_id);
}

int	check_one_dead_flag_activated(t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < philo->nb_philo)
	{
		if (philo->watcher->dead_flag == 1L)
			return (1);
		i++;
	}
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(checking_death(philo) == 0)
	{
		if (checking_death(philo) == 1)
			break ;
		if (break_conditions(philo) == 1)
			break ;
		eat(philo);
		if (break_conditions(philo) == 1)
			break ;
		philo_sleep(philo);
		if (checking_death(philo) == 1)
			break ;
		if (break_conditions(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}


