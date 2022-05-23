#include <semaphore.h>	/* sem_open(), sem_destroy(), sem_wait */
#include <stdlib.h> 	/* malloc, exit, free */
#include <stdio.h>		/* printf */
#include <unistd.h>		
#include <sys/types.h>	/* key_t, sem_t, pid_t */
#include <sys/wait.h>	
#include <sys/shm.h>	/* shmat(), IPC_RMID */
#include <fcntl.h>		/* O_CREAT, O_EXEC */
#include <errno.h>		/* errno, ECHILD */
# include <pthread.h>

int 	cnt;

int main(int argc, char **argv)
{
	sem_t			*ready;	// semaphore (shared)
	sem_t			*sema;	// semaphore (shared)
	pid_t			pid;
	int		i;
	int		n;

	sem_unlink("/test");
	ready = sem_open("/test", O_CREAT | O_EXCL, 0644, 1);
	sema = sem_open("/sema", O_CREAT | O_EXCL, 0644, 1);
	n = 1;
	int x = 0;
	pid = 0;
	for (i = 0; i < n; i++)
	{
		pid = fork();
		if (pid < 0)
			printf("FORK ERROR \n");
		else if (pid == 0)
			break;
	}
	
/* 부모 프로세스 */
	if (pid != 0)
	{
		sem_wait(ready);
		x++;
		printf("parent %d\n", x);
		// sem_post(ready);
	}
	else
	{
		sem_wait(ready);
		sem_post(ready);
		x += 8;
		printf("child %d\n", x);
		// sem_post(ready);
	}
	// sem_post(ready);
	pthread_join(pid,NULL);
	if (pid != 0)
		sem_post(ready);
	// sem_wait(ready);
	// write(1,"waiting",10);
	// sem_close(ready);
	// sem_unlink("/test");

}