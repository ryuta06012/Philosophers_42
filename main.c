/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/18 00:52:26 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*monitor(void *void_philo)
{
	t_philos	*philo;
	int		ate_count;

	philo = (t_philos *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->info->meal_check);
		if (philo->info->die_flg || philo->info->all_ate)
			break ;
		ate_count = philo->info->ate;
		if (ate_count && ate_count == philo->info->philo_num)
		{
			philo->info->all_ate = 1;
			printf("%lld, %d, %s\n", get_time(), philo->id, "all_ate!");
			break ;
		}
		//philo->limit = philo->t_last_meal + philo->info->death_time;
		if (!philo->is_eat && get_time() >= philo->limit)
		{
			philo->info->die_flg = 1;
			put_message(get_time(), philo->id, TYPE_DIED);
			//printf("philo_id = %d\n", philo->id);
			break ;
		}
		pthread_mutex_unlock(&philo->info->meal_check);
		pthread_mutex_unlock(&philo->mutex);
		usleep(500);
	}
	//printf("check\n");
	pthread_mutex_unlock(&philo->info->meal_check);
	//printf("check\n");
	pthread_mutex_unlock(&philo->mutex);
	//printf("check\n");
	//printf("id = %d\n", philo->id);
	return ((void *)0);
}

void	*philosopher(void *void_philo)
{
	t_philos	*philo;
	pthread_t	tid;

	philo = (t_philos *)void_philo;
	/* printf("philosopher_philo_id = %d\n", philo->id);
	printf("%lld\n", get_time()); */
	if (philo->id % 2 == 0)
		usleep(30);
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	pthread_create(&tid, NULL, monitor, (void *)void_philo);
	//printf("--------monitor-----\n");
	//pthread_detach(tid);
	//pthread_join(tid, NULL);
	while (1)
	{	
		//printf("------get_forks----\n");
		if (get_forks(philo) == -1)
			break ;
		//printf("------main_eat----\n");
		if (eat(philo) == -1)
		{
			//printf("------main_eat----\n");
			break ;
		}
		//printf("------main_put_forks----\n");
		if (put_forks(philo) == -1)
			break ;
		//printf("------main_philo_sleep----\n");
		if (philo_sleep(philo) == -1)
			break ;
		//printf("------main_think----\n");
		if (think(philo) == -1)
			break ;
	}
	//printf("philo_id = %d\n", philo->id);
	//pthread_mutex_unlock(&philo->info->meal_check);
	//printf("bbbbbbb\n");
	//pthread_detach(tid);
	pthread_join(tid, NULL);
	//printf("bcccccccc\n");
	return (NULL);
}

int	create_threads(t_philos *philo, int argc)
{
	int	i;
	int	philo_num;
	//pthread_t	tid;

	philo_num = philo->info->philo_num;
	i = 0;
	argc = 0;
	while (i < philo_num)
	{
		//printf("-----p_create----\n");
		//printf("philo_id = %d\n", philo->id);
		pthread_create(&(philo->thread_id), NULL, philosopher, philo);
		//usleep(100);
		//pthread_detach(tid);
		/* pthread_create(&(philo->thread_id), NULL, philosopher, philo);
		pthread_detach(philo->thread_id); */
		//usleep(100);
		//printf("-----p_create_end----\n");
		philo = philo->left;
		i++;
	}
	return (0);
}

int	wait_end_threads(t_philos *philo)
{
	int	i;
	int	philo_num;
	//int err;
	//pthread_t tid;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		//printf("---join-----\n");
		//printf("join_philo->id = %d\n", philo->id);
		pthread_join(philo->thread_id, NULL);
		//usleep(100);
		//if (err != 0)
			//printf("join thread error!!\n");
		//pthread_detach(philo->thread_id);
		//usleep(100);
		//printf("---join_end-----\n");

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
	//printf("---main-----\n");
	wait_end_threads(philo);
	//clear_philos(philo);
	//clear_rules(rules);
	return (0);
}