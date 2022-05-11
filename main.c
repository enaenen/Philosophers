/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:42 by wchae             #+#    #+#             */
/*   Updated: 2022/05/11 20:46:28 by wchae            ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	// t_philo		*philo;
	t_main_info	info;
	int			flag;

	flag = 0;
	if (parse(argc, argv, &info))
		return (program_exit(PARSE_ERROR));

}