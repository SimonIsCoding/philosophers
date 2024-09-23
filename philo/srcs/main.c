/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/23 19:37:35 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_states(t_philo *philo, t_states philo_state)
{
	if (philo_state == FORK)
		write_taken_fork_msg(philo);
	else if (philo_state == EAT)
		write_eat_msg(philo);
	else if (philo_state == SLEEP)
		write_sleep_msg(philo);
	else if (philo_state == THINK)
		write_think_msg(philo);
}

void	print(t_philo *philo, t_states philo_state)
{
	pthread_mutex_lock(&philo->watcher->dead_mutex);
	if (philo->watcher->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->watcher->dead_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->print_mutex);
	check_states(philo, philo_state);
	pthread_mutex_unlock(&philo->watcher->dead_mutex);
	pthread_mutex_unlock(&philo->print_mutex);
}

static int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		write_taken_fork_msg(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->print_mutex);
		precise_usleep(philo->time_to_die * 1000);
		write_dead_msg(philo);
		pthread_mutex_unlock(&philo->print_mutex);
		return (0);
	}
	init_threads(philo);
	return (0);
}

static int	destroy_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&philo->print_mutex) != 0)
		return (-1);
	if (pthread_mutex_destroy(&philo->watcher->dead_mutex) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	t_big			watch;

	if (check_error(argc, argv) == 1)
		return (1);
	watch.dead_flag = 0L;
	philo = init_philo_struct(argv, &watch);
	forks = init_forks(philo);
	if (!philo || !forks)
		return (2);
	start_philosophing(philo);
	destroy_forks(philo, forks);
	free(philo);
	free(forks);
	return (0);
}
