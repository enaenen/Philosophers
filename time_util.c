/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:09:34 by wchae             #+#    #+#             */
/*   Updated: 2022/05/21 22:09:39 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_timestamp	duration;
	t_timestamp	time_start;
	t_timestamp	time_cur;

	if (mode == 1)
		duration = info->tte;
	else if (mode == 2)
		duration = info->tts;
	time_start = get_time();
	while (!(info->finish))
	{
		time_cur = get_time();
		if (time_cur - time_start >= duration)
			return ;
		usleep(10);
	}
}
