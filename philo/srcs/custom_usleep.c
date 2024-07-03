/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:06:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/07/03 13:59:10 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000L
		+ (end.tv_usec - start.tv_usec));
}

void	precise_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	gettimeofday(&start, NULL);
	elapsed = usec + 1;
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

/*int	main(void)
{
	struct timeval	start;
	struct timeval	end;
	long			seconds;
	long			microseconds;
	double			elapsed;

	gettimeofday(&start, NULL);
	precise_usleep(500000);
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds + microseconds * 1e-6;
	printf("Expected sleep duration: "BOLD_RED"\t0.5"RESET" seconds\n");
	printf("Actual sleep duration: "BOLD_RED"\t\t%f"RESET" seconds\n", elapsed);
	return (0);
}
*/