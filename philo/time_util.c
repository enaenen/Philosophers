/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:09:34 by wchae             #+#    #+#             */
/*   Updated: 2022/05/22 15:13:15 by wchae            ###   ########.fr       */
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
	t_timestamp	limit;
	t_timestamp	start;
	t_timestamp	current;

	if (mode == 1)
		limit = info->tte;
	else if (mode == 2)
		limit = info->tts;
	start = get_time();
	while (!(info->finish))
	{
		current = get_time();
		if (limit <= current - start)
			return ;
		usleep(10);
	}
}
