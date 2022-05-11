#include <stdio.h>
#include <stdlib.h>

static int	ft_isdigit(const char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoll(char *str, long long *n)
{
	int len;

	len = 0;
	*n = 0;
	while (ft_isdigit(str[len]))
	{
		if (10 < len)
			break;
		*n = *n * 10 + (str[len] - '0');
		len++;
	}
	if (str[len] != '\0' || len == 0 || 4294967295U < *n || *n <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	long long n;

	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	if (argc != 2)
	{
		printf("Needs 1 INPUT\n");
		exit(0);
	}
	ft_atoll(argv[1], &n);
	printf("%lld", n);
}