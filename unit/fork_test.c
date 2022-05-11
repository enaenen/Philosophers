#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t	mutexes[NUM_THREADS];
pthread_cond_t conditionVars[NUM_THREADS];

int permits[NUM_THREADS];
pthread_t id[NUM_THREADS];

void pickup_forks(int philo_number)
{
	pthread_mutex_lock(&mutexes[philo_number % NUM_THREADS]);
	while (permits[philo_number % NUM_THREADS] == 0)
		pthread_cond_wait(&conditionVars[philo_number % NUM_THREADS], &mutexes[philo_number % NUM_THREADS]);
	permits[philo_number % NUM_THREADS] = 0;
	pthread_mutex_unlock(&mutexes[philo_number % NUM_THREADS]);
}

void return_forks(int philo_number)
{
	pthread_mutex_lock(&mutexes[philo_number % NUM_THREADS]);
	permits[philo_number % NUM_THREADS] = 1;
	pthread_cond_signal(&conditionVars[philo_number % NUM_THREADS]);
	pthread_mutex_unlock(&mutexes[philo_number % NUM_THREADS]);
}


void	*Philosoper(void *arg)
{
	int philo_number;
	philo_number = (int)arg;

	//pick up left fork
	pickup_forks(philo_number);
	printf("philosopher(%d) pick up the fork(%d).\n", philo_number, philo_number);
	//pick up right fork
	pickup_forks(philo_number + 1);
	printf("philosopher(%d) pick up the fork(%d).\n", philo_number, (philo_number + 1) % NUM_THREADS);
	
	printf("philosopher(%d) starts eating \n", philo_number);
    sleep(2);
    printf("philosopher(%d) finishes eating \n", philo_number);
 
    // putdown right fork
    return_forks(philo_number + 1);
    printf("philosopher(%d) put down the fork(%d).\n", philo_number, (philo_number + 1) % NUM_THREADS);
 
    // putdown left fork
    return_forks(philo_number);
    printf("philosopher(%d) put down the fork(%d).\n", philo_number, philo_number);
 
    return NULL;
	
}

void	*oddPhilosopher(void *arg)
{
 	int philo_number;
    philo_number = (int)arg;
 
    // pickup right fork
    pickup_forks(philo_number + 1);
    printf("philosopher(%d) picks up the fork(%d).\n", philo_number, (philo_number + 1) % NUM_THREADS);
 
    // pickup left fork
    pickup_forks(philo_number);
    printf("philosopher(%d) picks up the fork(%d).\n", philo_number, philo_number);
 
    printf("philosopher(%d) starts eating \n", philo_number);
    sleep(2);
    printf("philosopher(%d) finishes eating \n", philo_number);
 
    // putdown left fork
    return_forks(philo_number);
    printf("philosopher(%d) puts down the fork(%d).\n", philo_number, philo_number);
 
    // putdown right fork
    return_forks(philo_number + 1);
    printf("philosopher(%d) puts down the fork(%d).\n", philo_number, (philo_number + 1) % NUM_THREADS);
 
    return NULL;
}

int	main(void)
{
	int i;
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		pthread_cond_init(&conditionVars[i], NULL);
	}
	for (i = 0; i < NUM_THREADS; i++) {
        if (i % 2) {
            pthread_create(&id[i], NULL, oddPhilosopher, (void*)(i));
        }
        else{
            pthread_create(&id[i], NULL, Philosoper, (void*)(i));
        }
    }
 
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(id[i], NULL);
    }
 
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_mutex_destroy(&mutexes[i]);
        pthread_cond_destroy(&conditionVars[i]);
    }
 
    return 0;
}