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
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define C_NRML "\033[0m" 
# define C_RED "\033[31m" 
# define C_GREN "\033[32m"
# define C_YLLW "\033[33m" 
# define C_BLUE "\033[34m" 
# define C_PRPL "\033[35m"
# define C_DEFAULT "\x1b[0m"


typedef unsigned long long	t_timestamp;
typedef struct	s_info
{
	int	philos;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	must_eat;
	unsigned int	eat_finish;
	unsigned int	finish;
	t_timestamp		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eating;
}		t_info;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat_cnt;
	unsigned int	l_fork;
	unsigned int	r_fork;
	t_timestamp		time;
	pthread_t		thread_id;
	t_info			*info;
}	t_philo;

typedef struct s_table
{
	t_info	*info;
	t_philo	*philos;
}	t_table;

enum e_error_status
{
	ALLOC_ERROR,
	PARSE_ERROR,
	MUTEX_ERROR
};


void	init_philo(t_table *table);
size_t	ft_strlen(const char *s);
void	run(t_table *table);
int	parse(int argc, char **argv, t_table *table);


#endif