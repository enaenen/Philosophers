/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:42 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 21:16:54 by wchae            ###   ########.fr       */
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

void	program_exit(int status)
{
	char	*msg;

	if (!status)
		exit(EXIT_SUCCESS);
	if (status == PARSE_ERROR)
		msg = "INPUT ERROR usage : ./philo philos ttd tte tts [musteat]\n";
	if (status == ALLOC_ERROR)
		msg = "ALLOC ERROR\n";
	if (status == MUTEX_ERROR)
		msg = "MUTEX ERROR\n";
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(table->info->print), NULL))
		program_exit(MUTEX_ERROR);
	if (pthread_mutex_init(&(table->info->eating), NULL))
		program_exit(MUTEX_ERROR);
	table->info->forks = malloc(sizeof(pthread_mutex_t) * table->info->philos);
	if (!(table->info->forks))
		program_exit(ALLOC_ERROR);
	while (i < table->info->philos)
	{
		if (pthread_mutex_init(&(table->info->forks[i]), NULL))
			program_exit(MUTEX_ERROR);
		i++;
	}
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * (table->info->philos));
	if (!table->philos)
		program_exit(ALLOC_ERROR);
	while (i < table->info->philos)
	{
		table->philos[i].id = i;
		table->philos[i].l_fork = i;
		table->philos[i].r_fork = (i + 1) % table->info->philos;
		table->philos[i].eat_cnt = 0;
		table->philos[i].info = table->info;
		table->philos[i].last_eat_time = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table		table;

	parse(argc, argv, &table);
	init_table(&table);
	init_philo(&table);
	if (table.info->philos < 1)
		program_exit(PARSE_ERROR);
	philo_run(&table);
	return (0);
}
