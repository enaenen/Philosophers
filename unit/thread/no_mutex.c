#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 뮤텍스 객체 선언
pthread_mutex_t mutex_lock;
 
int g_count = 0;  // 쓰레드 공유자원.
 
 typedef struct s_arg
 {
     char *str;
     pthread_mutex_t mutex;
 }t_arg;

void *t_function(t_arg *data)
{
    int i;
    char* thread_name = data->str;
    // critical section
    g_count = 0;   // 쓰레드마다 0부터 시작.
    for (i = 0; i < 50; i++)
    {
        printf("%s COUNT %d\n", thread_name, g_count);
        g_count++;  // 쓰레드 공유자원, 1증가.
        sleep(1);
    }
    return (NULL);
}

int main()
{
    pthread_t p_thread1, p_thread2;
    int status;
    pthread_mutex_t	mutex;
    t_arg   arg;
    arg.str = "Thread1";

 	pthread_mutex_init(&arg.mutex, NULL);
    pthread_create(&p_thread1, NULL, t_function, &arg);
    arg.str = "Thread2";
    pthread_create(&p_thread2, NULL, t_function, &arg);
 
    pthread_join(p_thread1, &status);
    pthread_join(p_thread2, &status);
}