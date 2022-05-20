#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int flag;

void *thread(void *data)
{
    while (*(int *)data < 1000000)
    {
        if (!flag)
            continue;
        if (flag)
        {
            printf("thread in %d\n", *(int *)data);
            flag = 0;
        }
        (*(int *)data)++;
    }
    return (NULL);
}

int main(void)
{
    pthread_t tid;
    int i;
    pthread_create(&tid, NULL, thread, &i);
    i = 0;
    while (i < 1000000)
    {
        if (flag)
            continue;
        if (!flag)
        {
            printf("thread out %d\n", i);
            flag = 1;
        }
        i++;
    }
    i++;
}