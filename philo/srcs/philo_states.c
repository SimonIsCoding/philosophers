/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:31:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/11 14:22:13 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	dying_state_for_one_philo(t_philo *philo)
{
	precise_usleep(philo->time_to_die * 1000);
	printf("\033[1;38;5;214m%li %li is dead ⚰️\033[0m\n",
		timestamp_in_ms(philo->start_living), philo->thread_id);
	return ;
}
