/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:04:57 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 22:56:58 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_seamphore(t_table *table)
{
	sem_close(table->info->forks);
	sem_close(table->info->forks);
	sem_close(table->info->forks);
	sem_close(table->info->forks);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eating");
	sem_unlink("ready");
}

void	destory_philo(t_table *table)
{
	int	i;
	int	signal;

	i = 0;
	while (i < table->info->philos)
	{
		waitpid(-1, &signal, 0);
		if (signal)
		{
			i = 0;
			while (i < table->info->philos)
			{
				kill(table->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	close_seamphore(table);
	free(table->philos);
	free(table->info);
}

void	check_must_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->info->must_eat)
	{
		while (i < table->info->philos
			&& table->info->must_eat <= table->philos[i].eat_cnt)
			i++;
		if (i == table->info->philos)
			table->info->eat_finish = 1;
	}
}

void	philo_run(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->info->start_time = get_time();
	philo = table->philos;
	sem_wait(table->info->ready);
	while (i < table->info->philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			program_exit(FORK_ERROR);
		if (philo[i].pid == 0)
			routine(&philo[i]);
		i++;
	}
	sem_post(table->info->ready);
	destory_philo(table);
}
