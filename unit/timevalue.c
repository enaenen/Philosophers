#include <sys/time.h>
#include <stdio.h>
int main(void)
{
	struct timeval time;
	long long ret;

	gettimeofday(&time, NULL);
	printf("sec = %ld",time.tv_sec);
	printf("usec = %d",time.tv_usec);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("\n %lld \n ",ret);
}