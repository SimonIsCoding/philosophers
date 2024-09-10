/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/10 11:23:16 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	break_conditions(t_philo *philo)
{
	if (philo->nb_must_eat != -1 && philo->eating_times >= philo->nb_must_eat)
		return (1);
	else if (timestamp_in_ms(philo->time_last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("\033[1;38;5;214m%li %i is dead ⚰️\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
		pthread_mutex_unlock(&philo->print_mutex);
		return (1);
	}
	return (0);
}

/*void	print(t_philo *philo, char *msg)
{
	msg = NULL;
	(void)philo;
	pthread_mutex_lock(&philo->print_mutex);
//	printf("numero = %s\n", ft_itoa((int)timestamp_in_ms(philo->start_living)));
	//write(1, ft_itoa((int)timestamp_in_ms(philo->start_living)), ft_strlen(ft_itoa((int)timestamp_in_ms(philo->start_living))));
	//write(1, " ", 1);
//	write(1, "1\n", 2);
//	write(1, ft_itoa(philo->thread_id), ft_strlen(ft_itoa(philo->thread_id)));
//	write(1, " ", 1);
//	write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&philo->print_mutex);
//	write(1, "2\n", 2);
}*/

void	eat(t_philo *philo)
{
	struct timeval	reset;

	pthread_mutex_lock(&philo->print_mutex);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	printf("\033[1;38;5;196m%li %i has taken 1° fork 🍴\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;196m%li %i has taken 2° fork 🍴\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	printf("\033[1;38;5;93m%li %i is eating 🍝\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	pthread_mutex_unlock(&philo->print_mutex);
	precise_usleep(philo->time_to_eat * 1000);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
//	printf("eating_times value: %d\n", *eating_times);
	philo->eating_times++;
//	printf("eating_times value: %d\n", *eating_times);
//	printf("in eat function - eating_times memory address: %p\n", eating_times);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->print_mutex);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("\033[1;38;5;46m%li %i is sleeping 😴\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	precise_usleep(philo->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	if ((philo->thread_id + 1) % philo->nb_philo != 0)
		//printf("%li %i is thinking\n", timestamp_in_ms(philo->start_living), ((philo->thread_id + 1) % philo->nb_philo));
	printf("\033[1;38;5;21m%li %i is thinking 💭\033[0m\n", timestamp_in_ms(philo->start_living), philo->thread_id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(1)
	{
		//usleep(510 * 1000);
		if (break_conditions(philo) == 1)
			break ;
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}