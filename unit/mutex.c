#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	mutex;

int g_count = 0;

void *t_function(void *data)
{
	int i;
	char *thread_name = (char *)data;

	pthread_mutex_lock(&mutex);
	g_count = 0;
	for (i = 0; i < 3 ; i++)
	{
		printf("%s COUNT %d \n",thread_name, g_count);
		g_count++;
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
}
int main()
{
	pthread_t p_thread1, p_thread2;
	int status;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&p_thread1, NULL, t_function, (void*)"Thread1");
	pthread_create(&p_thread2, NULL, t_function, (void*)"Thread2");

	pthread_join(p_thread1, (void *)&status);
	pthread_join(p_thread2, (void *)&status);
}