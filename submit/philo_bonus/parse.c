/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:47:31 by wchae             #+#    #+#             */
/*   Updated: 2022/05/22 16:06:38 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_atoll(char *str, long long *n)
{
	int	i;

	i = 0;
	*n = 0;
	while (ft_isdigit(str[i]))
	{
		if (10 < i)
			break ;
		*n = *n * 10 + (str[i++] - '0');
	}
	if (str[i] != '\0' || i == 0 || 4294967295U < *n || *n <= 0)
		return (PARSE_ERROR);
	return (0);
}

static int	parse_5(char **argv, t_info *info)
{
	long long	n;

	if (ft_atoll(argv[1], &n))
		program_exit(PARSE_ERROR);
	info->philos = n;
	if (ft_atoll(argv[2], &n))
		program_exit(PARSE_ERROR);
	info->ttd = n;
	if (ft_atoll(argv[3], &n))
		program_exit(PARSE_ERROR);
	info->tte = n;
	if (ft_atoll(argv[4], &n))
		program_exit(PARSE_ERROR);
	info->tts = n;
	info->must_eat = 0;
	info->finish = 0;
	info->eat_finish = 0;
	return (0);
}

static int	parse_6(char **argv, t_info *info)
{
	long long	n;

	if (parse_5(argv, info))
		return (PARSE_ERROR);
	if (ft_atoll(argv[5], &n))
		return (PARSE_ERROR);
	info->must_eat = n;
	return (0);
}

void	parse(int argc, char **argv, t_table *table)
{
	table->info = (t_info *)malloc(sizeof(t_info));
	if (argc == 5)
		parse_5(argv, table->info);
	else if (argc == 6)
		parse_6(argv, table->info);
	else
		program_exit(PARSE_ERROR);
}
