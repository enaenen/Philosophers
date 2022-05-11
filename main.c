/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:42 by wchae             #+#    #+#             */
/*   Updated: 2022/05/12 01:45:50 by wchae            ###   ########.fr       */
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

static int	program_exit(int	status)
{
	char	*msg;

	if (!status)
		return (0);
	if (status == PARSE_ERROR)
		msg = "INPUT ERROR\n";

	write(2, msg, ft_strlen(msg));
	return (status);
}

void	init_forks(t_table *table)
{
	int	i;
	if (ptread_mutex_init(&(table->info->print), NULL))
		program_exit(MUTEX_ERROR);
	if (pthread_mutex_init(&(table->info->eating), NULL))
		program_exit(MUTEX_ERROR);
	table->info->forks = malloc(sizeof(pthread_mutex_t) * table->info->philos);
	if (!(table->info->forks))
		program_exit(ALLOC_ERROR);
	i = 0;
	while (i < table->info->philos)
	{
		if (pthread_mutex_init(&table->info->forks[i], NULL))
			program_exit(MUTEX_ERROR);
			i++;
	}
}

int		main(int argc, char **argv)
{
	t_main_info	info;
	t_table		table;
	int			flag;

	flag = 0;
	if (parse(argc, argv, &table))
		return (program_exit(PARSE_ERROR));
	init_forks(&table);
	// if ()

}