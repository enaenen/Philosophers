#include <stdio.h>
#include <unistd.h>
typedef struct s_person{
		
} t_person;
typedef struct s_test{
	pid_t pid;

} t_test;

// void forktesting(t_test )

int main(void)
{
	int	n = 4;
	int i =0;
	pid_t pids[5];

	printf("before in\n");
	while (i < n)
	{
		pids[i] = fork();
		// printf("pids[%d] = %d \n", i, pids[i]);

		if (pids[i] == 0)
			printf("i = %d \n", i);
		// else
			// printf("this is ParentProcess %d \n", i);
		i++;
	}
	printf("only one\n");
}