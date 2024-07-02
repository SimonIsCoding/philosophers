/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/02 17:24:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void	*thread_id(void *ptr)
{
	int			id_number;
	static int	i = 0;

	id_number = ++i;
	ptr = NULL;
	printf("Thread number %d executing\n", id_number);
	if (id_number % 2 == 0)
//	{
		printf("Magic in thread nb %d\n", id_number);
//	}
	sleep(3);
	printf("Ending thread number %d\n", id_number);
	return (NULL);
}*/

//pthread_mutex_t	mutex;
/*int	i = 0;

//we want to increment a simple value in two different mutex
//we want to protect the code from a race condition
void	*increment_number()
{
	while (i < 10000)
	{
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;

	pthread_create(&thread_1, NULL, &increment_number, NULL);
	pthread_create(&thread_2, NULL, &increment_number, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	
	printf("value of i = %i\n", i);
//	printf("back in main");
	return (0);
}*/

/*#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int 			mails = 0;
pthread_mutex_t	mutex;

void* routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
        mails++;
        // read mails
        // increment
        // write mails
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
    pthread_t p1;
	pthread_t p2;
	pthread_t p3;

	pthread_mutex_init(&mutex, NULL);
    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);
    pthread_create(&p3, NULL, &routine, NULL);
    pthread_join(p1, NULL);
	printf("mails in process 1 mail nb : %d\n", mails);
	pthread_join(p2, NULL);
	printf("mails in process 2 mail nb : %d\n", mails);
	pthread_join(p3, NULL);
	printf("mails in process 3 mail nb : %d\n", mails);
	pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}*/

/*int	array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void	*my_function(void *arg)
{
	int		index = *(int *)arg;
	int		sum;
	int		i;
	
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += array[index + i];
		i++;
	}
	//printf("array[index] = %d \n", array[*(int *)arg]);
	//free(arg);
	*(int *)arg = sum;
	return (arg);
}

int main(void)
{
	pthread_t	th[2];//this is a array of 10 threads
	int			i;
	int			*d;
	int			*result;
	int			total;
	
	i = 0;
	total = 0;
	while (i < 2)
	{
		d = malloc(sizeof(int));
		*d = i * 5;
		pthread_create(&th[i], NULL, &my_function, d);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		result = malloc(sizeof(int));
		pthread_join(th[i], (void **) &result);
		i++;
		total += *result;
		free(result);
	}
	printf("the total sum equals: %d\n", total);
	return (0);
}*/

// on a besoin de convertir chaque argument en entier
// pour le premier entier, ce sera notre nombre de threads

int	main(int argc, char **argv)
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	
	if (argc != 5 && argc != 6)
		return (write(2, "Arguments ill written.\n", 24), 1);
	else
	{
		if (check_error(argv) == 1)
			return (2);
		nb_philo = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
	}
	return (0);
}