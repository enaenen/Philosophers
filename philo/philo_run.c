/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:04:57 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 21:43:30 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->info->philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < table->info->philos)
		pthread_mutex_destroy(&(table->info->forks[i++]));
	pthread_mutex_destroy(&(table->info->print));
	pthread_mutex_destroy(&(table->info->eating));
	free(table->info->forks);
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

void	check_table(t_table *table)
{
	int		i;
	t_philo	*cur;

	while (!table->info->eat_finish)
	{
		i = 0;
		while (i < table->info->philos && !(table->info->finish))
		{
			pthread_mutex_lock(&(table->info->eating));
			cur = &(table->philos[i]);
			if (get_time() - cur->last_eat_time > table->info->ttd)
			{
				state_print(DEAD, table->info, i);
				table->info->finish = 1;
			}
			pthread_mutex_unlock(&(table->info->eating));
			i++;
		}
		if (table->info->finish)
			break ;
		check_must_eat(table);
	}
}

void	philo_run(t_table *table)
{
	int		i;
	void	*philo;

	i = 0;
	table->info->start_time = get_time();
	while (i < table->info->philos)
	{
		philo = (void *)&table->philos[i];
		if (pthread_create(&(table->philos[i].thread_id), NULL, routine, philo))
			program_exit(ALLOC_ERROR);
		table->philos[i].last_eat_time = get_time();
		i++;
	}
	check_table(table);
	destory_philo(table);
}
