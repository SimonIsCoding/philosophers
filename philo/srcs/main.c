/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:19 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//this function let us write the line for every philo's state
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

//we have to use the mutex to print every messages
//Otherwise the messages displayed would not be mixed up with other messages
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

//If there is 1 philo, there is one fork. In that case this philo won't be 
//able to eat because he need two forks. I could have use a mutex for the fork
//But I know that I will just print the messages, with the time_to_die delay
//The messages printed can not be mixed up thanks to this delay. 
//And I don't really need the use of a mutex.
//If there is more than 1 philo, we enter in init_threads to create every
//threads and enter in the routine
static int	start_philosophing(t_philo *philo)
{
	if (philo->nb_philo == 1)
	{
		write_taken_fork_msg(philo);
		precise_usleep(philo->time_to_die * 1000, philo);
		write_dead_msg(philo);
		return (0);
	}
	init_threads(philo);
	return (0);
}

//This function is used to destroy all the mutex that we have before going out
//of the programm
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

//Very important:
//When we exit from the program, every malloc has to be freed, every mutex has
//to be unlocked and destroyed and every threads has to be destroyed as well
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
