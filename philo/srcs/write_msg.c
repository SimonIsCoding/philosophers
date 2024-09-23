/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:22:18 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/23 15:26:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_taken_fork_msg(t_philo *philo)
{
	ft_putnbr(timestamp_in_ms(philo->start_living));
	write(1, " ", 1);
	ft_putnbr(philo->thread_id);
	write(1, " has taken a fork\n", 18);
}

void	write_eat_msg(t_philo *philo)
{
	ft_putnbr(timestamp_in_ms(philo->start_living));
	write(1, " ", 1);
	ft_putnbr(philo->thread_id);
	write(1, " is eating\n", 11);
}

void	write_sleep_msg(t_philo *philo)
{
	ft_putnbr(timestamp_in_ms(philo->start_living));
	write(1, " ", 1);
	ft_putnbr(philo->thread_id);
	write(1, " is sleeping\n", 13);
}

void	write_think_msg(t_philo *philo)
{
	ft_putnbr(timestamp_in_ms(philo->start_living));
	write(1, " ", 1);
	ft_putnbr(philo->thread_id);
	write(1, " is thinking\n", 13);
}

void	write_dead_msg(t_philo *philo)
{
	ft_putnbr(timestamp_in_ms(philo->start_living));
	write(1, " ", 1);
	ft_putnbr(philo->thread_id);
	write(1, " is dead\n", 9);
}