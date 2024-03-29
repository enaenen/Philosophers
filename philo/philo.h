/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:58 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 23:11:14 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define SLEEPING "\033[0m is sleeping\x1b[0m"
# define THINKING "\033[34m is thinking\x1b[0m"
# define TAKE_FORK "\033[32m has taken a fork\x1b[0m"
# define EATING "\033[33m is eating\x1b[0m"
# define DEAD "\033[31m died\x1b[0m"

typedef long long	t_timestamp;

typedef struct s_info
{
	int				philos;
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
	t_timestamp		last_eat_time;
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

enum e_checktime_mode
{
	EAT_CHECK,
	SLEEP_CHECK
};

void		init_table(t_table *table);
size_t		ft_strlen(const char *s);
void		philo_run(t_table *table);
void		parse(int argc, char **argv, t_table *table);
void		program_exit(int status);
t_timestamp	get_time(void);
void		check_time(t_info *info, int mode);
void		state_print(char *msg, t_info *info, int philo_id);
void		*routine(void *philo);

#endif