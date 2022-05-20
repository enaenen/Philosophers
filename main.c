/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:42 by wchae             #+#    #+#             */
/*   Updated: 2022/05/12 01:45:50 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	program_exit(int	status)
{
	char	*msg;

	if (!status)
		return (0);
	if (status == PARSE_ERROR)
		msg = "INPUT ERROR\n";

	write(2, msg, ft_strlen(msg));
	return (status);
}

void	init_forks(t_table *table)
{
	int i;
	if (pthread_mutex_init(&(table->info->print), NULL))
		printf("error\n");
		//error; mutex init failed
	if (pthread_mutex_init(&(table->info->eating), NULL))
		printf("error\n");
		//error  mutex init failed
	table->info->forks = malloc(sizeof(pthread_mutex_t) * table->info->philos);
	if (!(table->info->forks))
		printf("error\n");
		//error  - malloc forks array failed
	i = 0;
	while (i < table->info->philos)
	{
		if (pthread_mutex_init(&(table->info->forks[i]), NULL))
			printf("error\n");
			//error mutex init failed
		i++;
	}
}

void	init_philo(t_table *table)
{
	int	i;
	i = 0;
	table->philos = malloc(sizeof(t_philo) * (table->info->philos + 1));
	if (!table->philos)
		printf("error\n");
		//malloc philo failed;
	while (i < table->info->philos)
	{
		table->philos[i].id = i;
		table->philos[i].l_fork = i;
		table->philos[i].r_fork = (i + 1) % table->info->philos;
		table->philos[i].eat_cnt = 0;
		table->philos[i].info = table->info;
		table->philos[i].time = 0;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_table		table;
	int			flag;

	flag = 0;
	if (parse(argc, argv, &table))
		return (program_exit(PARSE_ERROR));
	init_forks(&table);
	init_philo(&table);
	if (table.info->philos < 1)
		exit(1);
	run(&table);
	return (0);
}