/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:42 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 21:57:45 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	else if (status == PARSE_ERROR)
		msg = "INPUT ERROR usage : ./philo philos ttd tte tts [musteat]\n";
	else if (status == ALLOC_ERROR)
		msg = "ALLOC ERROR\n";
	else if (status == SEMAP_ERROR)
		msg = "SEMAPHORE ERROR\n";
	else if (status == FORK_ERROR)
		msg = "FORK_ERROR\n";
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	init_table(t_table *table)
{
	t_info	*info;

	info = table->info;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eating");
	sem_unlink("/ready");
	info->forks = sem_open("/forks", O_CREAT, 0644, info->philos);
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	info->eating = sem_open("/eating", O_CREAT, 0644, 1);
	info->ready = sem_open("/ready", O_CREAT, 0644, 1);
	if (!(info->ready && info->print && info->eating && info->ready))
		program_exit(SEMAP_ERROR);
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
