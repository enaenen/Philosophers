/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:09:34 by wchae             #+#    #+#             */
/*   Updated: 2022/05/22 17:35:22 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_timestamp	get_time(void)
{
	t_timestamp		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

void	check_time(t_info *info, int mode)
{
	t_timestamp	limit;
	t_timestamp	start;

	if (mode == EAT_CHECK)
		limit = info->tte;
	else if (mode == SLEEP_CHECK)
		limit = info->tts;
	start = get_time();
	while (!(info->finish))
	{
		if (limit <= get_time() - start)
			return ;
		usleep(500);
	}
}

void	delay_time(t_info *info, t_philo *cur)
{
	t_timestamp	limit;
	t_timestamp	start;

	start = cur->last_eat_time;
	limit = info->ttd * 0.8;
	while (limit >= get_time() - start)
	{
		usleep(500);
	}
}
