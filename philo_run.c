#include "philo.h"

t_timestamp get_time(void)
{
    t_timestamp     ret;
    struct timeval  time;

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

void	philo_print(char *msg, t_info *info, int philo_id)
{
	pthread_mutex_lock(&(info->print));
	if (!(info->finish) && !(info->eat_finish))
	{
		printf("%lld ", get_time() - info->start_time);
		printf("%d ", philo_id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(info->print));
}

int	philo_even(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	philo_print(TAKE_FORK, info, philo->id);
	if (philo->r_fork == philo->l_fork)
	{
		pthread_mutex_unlock(&(info->forks[philo->l_fork]));
		return (1);
	}
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	philo_print(TAKE_FORK, info, philo->id);
	pthread_mutex_lock(&(info->eating));
	philo_print(EATING, info, philo->id);
	philo->time = get_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&(info->eating));
	check_time(info, 1);
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	if (info->eat_finish || info->finish)
		return (1);
	return (0);
}

int	philo_odd(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	philo_print(TAKE_FORK, info, philo->id);
	if (philo->r_fork == philo->l_fork)
	{
		pthread_mutex_unlock(&(info->forks[philo->r_fork]));
		return (1);
	}
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	philo_print(TAKE_FORK, info, philo->id);
	pthread_mutex_lock(&(info->eating));
	philo_print(EATING, info, philo->id);
	philo->time = get_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&(info->eating));
	check_time(info, 1);
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	if (info->eat_finish || info->finish)
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_info	*info;
	t_philo	*cur;
	int		flag;

	cur = (t_philo *)philo;
	info = cur->info;
	flag = 0;
	if (cur->id % 2)
		usleep(10000);
	while (!info->finish && !info->eat_finish)
	{
		if (cur->id % 2 == 0)
			flag = philo_even(info, cur);
		else
			flag = philo_odd(info, cur);
		if (flag)
			break ;
		philo_print(SLEEPING, info, cur->id);
		check_time(info, 2);
		philo_print(THINKING, info, cur->id);
		usleep(10);
	}
	return (0);
}

void	destory_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->info->philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < table->info->philos)
		pthread_mutex_destroy(&(table->info->forks[i++]));
	pthread_mutex_destroy(&(table->info->print));
	pthread_mutex_destroy(&(table->info->eating));
	free(table->info->forks);
	free(table->philos);
	free(table->info);
}

void	check_must_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->info->must_eat)
	{
		while (i < table->info->philos
			&& table->info->must_eat <= table->philos[i].eat_cnt)
			i++;
		if (i == table->info->philos)
			table->info->eat_finish = 1;
	}
}

void	check_table(t_table *table)
{
	int		i;
	t_philo	*cur;

	while (!table->info->eat_finish)
	{
		i = 0;
		while (i < table->info->philos && !(table->info->finish))
		{
			pthread_mutex_lock(&(table->info->eating));
			cur = &(table->philos[i]);
			if (get_time() - cur->time > table->info->ttd)
			{
				philo_print(DEAD, table->info, i);
				table->info->finish = 1;
			}
			pthread_mutex_unlock(&(table->info->eating));
			i++;
		}
		if (table->info->finish)
			break ;
		check_must_eat(table);
	}
}

void	run(t_table *table)
{
	int		i;
	void	*tmp;

	i = 0;
	table->info->start_time = get_time();
    while (i < table->info->philos)
    {
        tmp = (void *)&table->philos[i];
        if (pthread_create(&(table->philos[i].thread_id), NULL, routine,tmp))
			program_exit(ALLOC_ERROR);
        table->philos[i].time = get_time();
        i++;
    }
    check_table(table);
    destory_philo(table);
}
