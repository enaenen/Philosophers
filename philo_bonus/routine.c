/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:07:29 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 22:57:05 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	state_print(char *msg, t_info *info, int philo_id)
{
	sem_wait(info->print);
	if (!(info->finish))
	{
		printf("%lld ", get_time() - info->start_time);
		printf("%d ", philo_id + 1);
		printf("%s\n", msg);
	}
	sem_post(info->print);
}

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	state_print(TAKE_FORK, info, philo->id);
	sem_wait(info->forks);
	state_print(TAKE_FORK, info, philo->id);
	sem_wait(info->eating);
	state_print(EATING, info, philo->id);
	philo->last_eat_time = get_time();
	sem_post(info->eating);
	check_time(info, EAT_CHECK);
	(philo->eat_cnt)++;
	sem_post(info->forks);
	sem_post(info->forks);
}

void	*checking(void	*tmp)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *)tmp;
	info = philo->info;
	while (1)
	{
		sem_wait(info->eating);
		if (info->ttd < get_time() - philo->last_eat_time)
		{
			state_print(DEAD, info, philo->id);
			info->finish = 1;
			sem_wait(info->print);
			exit(1);
		}
		sem_post(info->eating);
		if (info->finish)
			break ;
		usleep(100);
		if (info->must_eat && info->must_eat <= philo->eat_cnt)
			break ;
	}
	return (0);
}

void	routine(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	philo->last_eat_time = get_time();
	pthread_create(&(philo->check), NULL, *checking, (void *)philo);
	sem_wait(info->ready);
	sem_post(info->ready);
	if (philo->id % 2)
		usleep(10000);
	while (!info->finish)
	{
		eating(philo);
		if (info->must_eat && info->must_eat <= philo->eat_cnt)
			break ;
		state_print(SLEEPING, info, philo->id);
		check_time(info, SLEEP_CHECK);
		state_print(THINKING, info, philo->id);
		usleep(10);
	}
	pthread_join(philo->check, NULL);
	if (philo->info->finish)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
