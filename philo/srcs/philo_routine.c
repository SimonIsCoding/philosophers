/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/26 19:08:41 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Here we want to pick the forks in the same order to avoid data races
//For this we compare the memory adresses for each forks
//Given that every pointer are unsigned int (type uintptr_t) we can use this (<)
//operator to select which one we use first. And every philos will follow this
//strict way to choose their forks to avoid data races.
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

//To eat, all the philos need 2 forks (left & right), picking them in the exact
//strict order. Otherwise we will have data races. When a philo, starts to pick
//a fork we directly lock the second one to avoid two philos beside each other
//to pick only one fork.
//If they pick only one fork, they  will not be abe to eat (because they need 2)
//When the philos starts to eat, we reset their time of life (=time_to_die) to 0
static void	eat(t_philo *philo)
{
	struct timeval	reset;

	if (checking_death(philo) == 1)
		return ;
	pick_correct_fork(philo);
	print(philo, FORK);
	print(philo, FORK);
	print(philo, EAT);
	gettimeofday(&reset, NULL);
	philo->time_last_meal = reset;
	precise_usleep(philo->time_to_eat * 1000, philo);
	philo->eating_times++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	if (break_conditions(philo) == 1)
		return ;
	print(philo, SLEEP);
	precise_usleep(philo->time_to_sleep * 1000, philo);
}

//To create the routine, the philo has to think a special amount of time to make
//them all do the routine without breaking it. Depending on the input the user
//writes, each philo will think a certain time, or not.
//It is not mandatory to think. For some inputs, the philosophers can only
//eat && sleep in the routine without dying.
static void	think(t_philo *philo)
{
	if (checking_death(philo) == 1)
		return ;
	if (philo->nb_philo % 2 == 0 && philo->time_to_eat > philo->time_to_sleep)
	{
		print(philo, THINK);
		precise_usleep((philo->time_to_eat - philo->time_to_sleep) * 1000, philo);
	}
	if (philo->nb_philo % 2 == 1)
	{
		print(philo, THINK);
		precise_usleep((philo->time_to_eat * 2 - philo->time_to_sleep) * 1000, philo);
	}
}

//In the function pthread_create, we pass as the fourth argument our &philo[i]
//but the function philo_routine has a strict prototype which is:
//void	*routine(void *arg)
//It means that the pointer of &philo[i] is now in arg
//Then we create the t_philo type variable to be able to cast our arg in philo
//and receive all the information that we had in the array of philo[i]
//For each actions we need to check if every philo are alive, otherwise we will
//display a msg saying that one pphilo is dead, and another one will continue 
//to sleep or think
//If no philo dies and there is no limit of meals, the while loop is infinite
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (break_conditions(philo) == 0)
	{
		eat(philo);
		if (break_conditions(philo) == 1)
			break ;
		philo_sleep(philo);
		if (break_conditions(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}
