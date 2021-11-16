/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/16 07:50:54 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
/* 
void	*monitor_count(void *void_info)
{
	t_rules	*info;
	int		ate_count;
	int		philo_num;

	info = (t_rules *)void_info;
	philo_num = info->philo_num;
	while (1)
	{
		pthread_mutex_lock(&info->meal_check);
		ate_count = info->ate;
		printf("ate_count = %d\n", ate_count);
		if (ate_count && ate_count == info->philo_num)
		{
			info->all_ate = 1;
			pthread_mutex_unlock(&info->meal_check);
			break ;
		}
		pthread_mutex_unlock(&info->meal_check);
		usleep(1000);
	}
	return ((void *)0);
} */

void	*monitor(void *void_philo)
{
	t_philos	*philo;
	int		ate_count;

	philo = (t_philos *)void_philo;
	while (1)
	{
		if (philo->info->die_flg || philo->info->all_ate)
			return ((void *)0);
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->info->meal_check);
		ate_count = philo->info->ate;
		//printf("ate_count = %d\n", ate_count);
		if (ate_count && ate_count == philo->info->philo_num)
		{
			philo->info->all_ate = 1;
			printf("%lld, %d, %s\n", get_time(), philo->id, "all_ate!");
			break ;
		}
		philo->limit = philo->t_last_meal + philo->info->death_time;
		if (get_time() >= philo->limit)
		{
			philo->info->die_flg = 1;
			put_message(get_time(), philo->id, TYPE_DIED);
			break ;
		}
		pthread_mutex_unlock(&philo->info->meal_check);
		pthread_mutex_unlock(&philo->mutex);
		usleep(5);
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_unlock(&philo->mutex);
	return ((void *)0);
}

void	*philosopher(void *void_philo)
{
	t_philos	*philo;
	pthread_t	tid;

	philo = (t_philos *)void_philo;
	if (philo->id % 2 == 0)
		usleep(5000);
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	pthread_create(&tid, NULL, monitor, (void *)void_philo);
	pthread_detach(tid);
	//pthread_join(tid, NULL);
	while (1)
	{	
		if (get_forks(philo) == -1)
			break ;
		if (eat(philo) == -1)
		{
			printf("------main_eat----\n");
			break ;
		}
		put_forks(philo);
		if (philo_sleep(philo) == -1)
			break ;
		if (think(philo) == -1)
			break ;
	}
	printf("philo_id = %d\n", philo->id);
	//pthread_mutex_unlock(&philo->info->meal_check);
	printf("bbbbbbb\n");
	//pthread_detach(tid);
	//pthread_join(tid, NULL);
	printf("bcccccccc\n");
	return (NULL);
}

int	create_threads(t_philos *philo, int argc)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	argc = 0;
	while (i < philo_num)
	{
		printf("-----p_create----\n");
		pthread_create(&(philo->thread_id), NULL, philosopher, philo);
		printf("-----p_create_end----\n");
		philo = philo->left;
		i++;
	}
	return (0);
}

int	wait_end_threads(t_philos *philo)
{
	int	i;
	int	philo_num;
	int err;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		printf("---join-----\n");
		printf("join_philo->id = %d\n", philo->id);
		err = pthread_join(philo->thread_id, NULL);
		if (err != 0)
			printf("join thread error!!\n");
		//pthread_detach(philo->thread_id);
		printf("---join_end-----\n");
		philo = philo->left;
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_philos	*philo;
	t_rules		*rules;
	//int		i;

	if (argc <= 4)
		return (-1); //とりあえず、設定。
	rules = init_rules(argv);
	philo = create_struct_philo(rules->philo_num);
	create_philo(philo, rules);
	/* int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		printf("philo_id = %d, i = %d\n", philo->id, i);
		i++;
		philo = philo->left;
	}
	return (0); */
	create_threads(philo, argc);
	wait_end_threads(philo);
	//clear_philos(philo);
	//clear_rules(rules);
	return (0);
}