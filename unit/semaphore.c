#include <semaphore.h>	/* sem_open(), sem_destroy(), sem_wait */
#include <stdlib.h> 	/* malloc, exit, free */
#include <stdio.h>		/* printf */
#include <unistd.h>		
#include <sys/types.h>	/* key_t, sem_t, pid_t */
#include <sys/wait.h>	
#include <sys/shm.h>	/* shmat(), IPC_RMID */
#include <fcntl.h>		/* O_CREAT, O_EXEC */
#include <errno.h>		/* errno, ECHILD */

int	main(int argc, char **argv)
{
	int				i;
	int				shmid;	// shared memory id;
	key_t			shmkey; // shared memory key;
	sem_t			*sem;	// semaphore (shared)
	pid_t			pid;	// fork pid;
	int				*p;		// shared variable
	unsigned int	n;		//fork count
	unsigned int	value;	//semaphore value

	/* 공유메모리 초기화 */
	shmkey = ftok("/dev/null", 5);
	printf("shmkey for p = %d\n", shmkey);
	shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
	
	/* 공유메모리 유효성 체크 */
	if (shmid < 0)
	{
		perror ("shmget\n");
		exit (1);
	}
	/* p를 공유메모리로 지정 */
	p = (int *) shmat (shmid, NULL, 0);
	*p = 0;
	printf("p = %d is allocated in shared memory.\n\n", *p);


	printf("만들 자식프로세스 개수 :  \n");
	scanf("%u", &n);

	printf("세마포어 값 설정 : ");
	scanf("%u", &value);

	/* 세마포어 값 초기화 
		pSem 의 이름으로 세마포어 생성
	*/
	sem = sem_open("pSem", O_CREAT | O_EXCL, 0644, value);
	/* unlink를 하여 세마포어가 계속 존재하는것을 방지 (실행 중 충돌이 생기는것을 방지)*/
	sem_unlink("pSem");
	printf("semaphores initialized.\n\n");

	/* fork child process */
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
		while ((pid = waitpid (-1, NULL, 0)) > 0)
			if (errno == ECHILD)
				break;
		printf("\n Parent : 모든 자식 프로세스가 종료되었습니다.\n");

		/*공유 메모리 detach*/
		shmdt (p);
		shmctl (shmid, IPC_RMID, 0);

		/* 세마포어 삭제 */
		sem_unlink("pSem");
		sem_close(sem);

		exit (0);
		
	}
	else
	{
		sem_wait (sem); // P 연산
		printf("	Child(%d) is in critial seciton\n", i);
		// sleep(1);
		*p += i % 3;
		printf ("	Child(%d) new value of *p = %d.\n", i, *p);
		sem_post(sem); // V 연산
		exit (0);
	}
	
}