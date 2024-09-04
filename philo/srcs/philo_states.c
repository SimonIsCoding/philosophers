/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/04 13:14:16 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void	print_mutexed(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	
	pthread_mutex_unlock(philo->mutex);
}*/

//This function should have mutex. The printf can be altered.
void	dying_state_for_one_philo(t_philo *philo)
{
	precise_usleep(philo->time_to_die * 1000);
	printf("%li 1 died\n", timestamp_in_ms(philo->start_living));
	return ;
}

/*{
	pthread_t	thread[philo->nb_philo];
	int			i;

	i = 0;
	//printf("nb_philo = %i\n", philo->nb_philo);
	while (i < philo->nb_philo)
	{
		philo->left_fork = forks[i];
		philo->right_fork = forks[(i + 1) % philo->nb_philo];
		pthread_create(&thread[i], NULL, &routine, &philo[i]);
		//printf("i = %i\n", i);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}*/
