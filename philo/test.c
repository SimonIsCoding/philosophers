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

int main() {
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

int main()
{
    struct timeval start, end;

    gettimeofday(&start, NULL); // Get the current time before sleeping
    usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
    gettimeofday(&end, NULL);  // Get the time after sleeping

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
    printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

    return 0;
}