/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/05 12:12:36 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//This function should have mutex. The printf can be altered.
void	dying_state_for_one_philo(t_philo *philo)
{
	precise_usleep(philo->time_to_die * 1000);
	printf("%li 1 died\n", timestamp_in_ms(philo->start_living));
	return ;
}

