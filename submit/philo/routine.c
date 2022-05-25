/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:07:29 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 21:44:57 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_print(char *msg, t_info *info, int philo_id)
{
	pthread_mutex_lock(&(info->print));
	if (!(info->finish) && !(info->eat_finish))
		printf("%lld %d %s\n",
			get_time() - info->start_time, philo_id + 1, msg);
	pthread_mutex_unlock(&(info->print));
}

int	philo_even(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	state_print(TAKE_FORK, info, philo->id);
	if (philo->r_fork == philo->l_fork)
	{
		pthread_mutex_unlock(&(info->forks[philo->l_fork]));
		return (1);
	}
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	state_print(TAKE_FORK, info, philo->id);
	pthread_mutex_lock(&(info->eating));
	state_print(EATING, info, philo->id);
	philo->last_eat_time = get_time();
	(philo->eat_cnt)++;
	pthread_mutex_unlock(&(info->eating));
	check_time(info, EAT_CHECK);
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	if (info->eat_finish || info->finish)
		return (1);
	return (0);
}

int	philo_odd(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	state_print(TAKE_FORK, info, philo->id);
	if (philo->r_fork == philo->l_fork)
	{
		pthread_mutex_unlock(&(info->forks[philo->r_fork]));
		return (1);
	}
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	state_print(TAKE_FORK, info, philo->id);
	pthread_mutex_lock(&(info->eating));
	state_print(EATING, info, philo->id);
	philo->last_eat_time = get_time();
	(philo->eat_cnt)++;
	pthread_mutex_unlock(&(info->eating));
	check_time(info, EAT_CHECK);
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	if (info->eat_finish || info->finish)
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_info	*info;
	t_philo	*cur;
	int		flag;

	cur = (t_philo *)philo;
	info = cur->info;
	flag = 0;
	pthread_mutex_lock(&(info->shared));
	cur->last_eat_time = info->start_time;
	info->wait_cnt++;
	pthread_mutex_unlock(&(info->shared));
	if (cur->id % 2)
		usleep(5000);
	while (!info->finish && !info->eat_finish)
	{
		if (cur->id % 2 == 0)
			flag = philo_even(info, cur);
		else
			flag = philo_odd(info, cur);
		if (flag)
			break ;
		state_print(SLEEPING, info, cur->id);
		check_time(info, SLEEP_CHECK);
		state_print(THINKING, info, cur->id);
		delay_time(info, cur);
		//usleep(500);
	}
	return (0);
}
