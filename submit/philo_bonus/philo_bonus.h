/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <wchae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:18:58 by wchae             #+#    #+#             */
/*   Updated: 2022/05/23 23:09:57 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eating;
	sem_t			*ready;
}		t_info;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat_cnt;
	t_timestamp		last_eat_time;
	pthread_t		check;
	pid_t			pid;
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
	SEMAP_ERROR,
	FORK_ERROR
};

enum e_print_mode
{
	EAT_CHECK,
	SLEEP_CHECK
};

void		init_philo(t_table *table);
size_t		ft_strlen(const char *s);
void		philo_run(t_table *table);
void		parse(int argc, char **argv, t_table *table);
void		program_exit(int status);
void		check_time(t_info *info, int mode);
void		state_print(char *msg, t_info *info, int philo_id);
void		routine(t_philo *philo);
t_timestamp	get_time(void);

#endif