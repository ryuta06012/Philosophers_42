/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/13 23:21:29 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
	return (NULL);
}

void	*monitor(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->info->meal_check);
		philo->limit = philo->t_last_meal + philo->info->death_time;
		//printf("limit = %lld\nnow = %lld\n", philo->limit, get_time());
		if (get_time() >= philo->limit)
		{
			philo->info->die_flg = 1;
			put_message(get_time(), philo->id, TYPE_DIED);
			break ;
		}
		pthread_mutex_unlock(&philo->info->meal_check);
		pthread_mutex_unlock(&philo->mutex);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

void	*philosopher(void *void_philo)
{
	t_philos	*philo;
	pthread_t	tid;
	int	i;

	philo = (t_philos *)void_philo;
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	pthread_create(&tid, NULL, monitor, (void *)philo);
	pthread_detach(tid);
	//pthread_join(tid, NULL);
	i = 0;
	while (1)
	{	

		get_forks(philo);
		eat(philo);
		pthread_mutex_lock(&philo->info->meal_check);
		if (philo->info->all_ate || philo->info->die_flg)
			break ;
		pthread_mutex_unlock(&philo->info->meal_check);
		put_forks(philo);
		philo_sleep(philo);
		think(philo);
		i++;
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	//pthread_join(tid, NULL);
	return (NULL);
}

int	create_threads(t_philos *philo, int argc)
{
	int	i;
	int	philo_num;
	pthread_t	tid;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		pthread_create(&(philo->thread_id), NULL, philosopher, philo);
		philo = philo->left;
		i++;
	}
	if (argc == 6)
	{
		printf("--monitor_count---\n");
		pthread_create(&tid, NULL, monitor_count, philo->info);
		pthread_detach(tid);
	}
	return (0);
}

int	wait_end_threads(t_philos *philo)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		printf("---join-----\n");
		printf("philo->id = %d\n", philo->id);
		//pthread_join(philo->thread_id, NULL);
		pthread_detach(philo->thread_id);
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

	if (argc < 1)
		return (-1); //とりあえず、設定。
	rules = init_rules(argv);
	philo = create_struct_philo(rules->philo_num);
	create_philo(philo, rules);
	create_threads(philo, argc);
	wait_end_threads(philo);
	clear_philos(philo);
	clear_rules(rules);
	return (0);
}