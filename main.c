/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/11 14:58:23 by hryuuta          ###   ########.fr       */
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

	philo = (t_philos *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eat && get_time() >= philo->limit)
		{
			put_message(get_time(), philo->id, TYPE_DIED);
			pthread_mutex_unlock(&philo->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	*philosopher(void *void_philo)
{
	t_philos	*philo;
	pthread_t	tid;
	int	i;

	philo = (t_philos *)void_philo;
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	pthread_create(&tid, NULL, monitor, void_philo);
	i = 0;
	while (i < 10)
	{
		get_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);//philo_sleep();
		think(philo);
		i++;
	}
	pthread_join(tid, NULL);
	return (NULL);
}

int	create_threads(t_philos *philo)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	if (philo)
	while (i < philo_num)
	{
		pthread_create(&(philo->thread_id), NULL, philosopher, philo);
		philo = philo->left;
		i++;
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
		pthread_join(philo->thread_id, NULL);
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

	if (argc < 0)
		return (-1); //とりあえず、設定。
	rules = init_rules(argv);
	philo = create_struct_philo(rules->philo_num);
	create_philo(philo, rules);
	create_threads(philo);
	wait_end_threads(philo);
	return (0);
}