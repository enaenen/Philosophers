/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:58 by wchae             #+#    #+#             */
/*   Updated: 2022/05/11 20:40:25 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long long	t_timestamp;
typedef struct	s_philo
{
	unsigned int	id;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	n_eat;
	t_timestamp		started_at;
	t_timestamp		last_eat;

}		t_philo;

typedef struct s_main_info
{
	unsigned int	philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	must_eat;
	unsigned int	option;
}	t_main_info;

enum e_error_status
{
	ALLOC_ERROR,
	PARSE_ERROR,
	MUTEX_ERROR
};

int	parse(int argc, char **argv, t_main_info *info);


#endif