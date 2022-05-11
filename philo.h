/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:58 by wchae             #+#    #+#             */
/*   Updated: 2022/05/12 01:43:14 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef unsigned long long	t_timestamp;
typedef struct	s_philo
{
	unsigned int	id;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	must_eat;
	t_timestamp		started_at;
	t_timestamp		last_eat;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
}		t_philo;

typedef struct s_main_info
{
	unsigned int	philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	must_eat;
	unsigned int	eat_finish;
	unsigned int	option;
	int				finish;
	t_timestamp		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eating;
}	t_main_info;

typedef struct s_table
{
	t_main_info	*info;
	t_philo	*philos;
}	t_table;

enum e_error_status
{
	ALLOC_ERROR,
	PARSE_ERROR,
	MUTEX_ERROR
};

int	parse(int argc, char **argv, t_main_info *info);


#endif