/*#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* thread_func(void* arg) 
{
    printf("Hello from the thread!\n");
    return NULL;
}

int main() 
{
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, thread_func, NULL) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }

    // Give the thread some time to execute.
    sleep(2);

    // 🚨🚨 Uncomment the following line to reclaim resources of the thread, 
    // preventing the leak.🚨🚨
    pthread_join(thread_id, NULL);

    printf("Exiting main function.\n");
    return 0;
}*/

/*
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // for sleep

// This function will be executed by the detached thread
void* print_in_background(void* arg)
{
    printf("This is printed from the thread.\n");
    sleep(2);
    return NULL;
}

int main()
{
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, print_in_background, NULL) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }

    // 🚨 toggle these 2 🚨
    //pthread_detach(thread_id);
    pthread_join(thread_id, NULL);

    // Continue with the main thread's work
    printf("This is printed from the main thread.\n");
    usleep(100000);

    return 0;
}*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// Define ANSI escape sequences for colors and styles
#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

/*int main()
{
    struct timeval start, end;
	int	begin, fin;

    begin = gettimeofday(&start, NULL); // Get the current time before sleeping
	printf("begin = %i\n", begin);
    usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
    fin = gettimeofday(&end, NULL);  // Get the time after sleeping
	printf("fin = %i\n", fin);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
    printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

    return 0;
}*/

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
	pthread_t	th[nb_of_philo]
	th[i]
	i++

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
	pthread_t	th[nb_philo];//this is a array of 2 threads
	int i = 0;
	while (i < nb_philo)
		thread_create(th[i], NULL, my_function, NULL)
	
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

/*
int	rate_time(void)
{
	int				requested_sleep_time;
	int				actual_time;
	struct timeval	start;
	struct timeval	end;

	requested_sleep_time = 2 * 1000000;
	printf("requested_sleep_time = 2 seconds = 2 000 000 microseconds\n");
	gettimeofday(&start, NULL);
	usleep(requested_sleep_time);
	gettimeofday(&end, NULL);
	actual_time = (end.tv_sec - start.tv_sec) * 10000000 + (end.tv_usec - start.tv_usec);
	printf("actual_time slept = %d\n", actual_time);
	return (0);
}

int main(void)
{
	rate_time();
	return (0);
}*/

long	get_elapsed_time_microseconds(struct timeval start,
						struct timeval end)
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
	gettimeofday(&current, NULL);
	elapsed = get_elapsed_time_microseconds(start, current);
	rem = usec - elapsed;
	if (rem > 1000)
		usleep(rem / 2);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

int	main(void)
{
	struct timeval	start;
	struct timeval	end;
	long int		temps_ecoule_en_ms;

	gettimeofday(&start, NULL);
	printf("start.tv_sec = %li\n", start.tv_sec);
	precise_usleep(1 * 1000000);
	gettimeofday(&end, NULL);
	printf("end.tv_sec = %li\n", end.tv_sec);

	long int	sec;
	long int	usec;

	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	long int temps_ecoule_en_us = (sec * 1000000L) + (usec);
	temps_ecoule_en_ms = (sec * 1000L) + (usec / 1000L);
	long int temps_ecoule_en_sec = (sec) + (usec / 1000000L);

	printf("sec = %li\n", sec);
	printf("usec = %li\n", usec);
	printf("temps_ecoule_en_us = %li\n", temps_ecoule_en_us);
	printf("temps_ecoule_en_ms = %li\n", temps_ecoule_en_ms);
	printf("temps_ecoule_en_sec = %li\n\n", temps_ecoule_en_sec);

	return (0);
}