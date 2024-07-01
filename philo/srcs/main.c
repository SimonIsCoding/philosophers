/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:09:47 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/01 17:30:36 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*thread_id(void *ptr)
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
}

int	main(void)
{
	pthread_t	thread;
	int			check_1;
	int			check_2;

	check_1 = pthread_create(&thread, NULL, &thread_id, NULL);
	check_2 = pthread_create(&thread, NULL, &thread_id, NULL);
	if (check_1 == -1 || check_2 == -1)
		return (1);
	check_1 = pthread_join(thread, NULL);
	check_2 = pthread_join(thread, NULL);
	if (check_1 == -1 || check_2 == -1)
		return (1);
	printf("back in main");
	return (0);
}
