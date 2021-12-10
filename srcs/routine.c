/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:45:16 by hryuuta           #+#    #+#             */
/*   Updated: 2021/12/06 07:53:52 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor(void *void_philo)
{
	t_plst	*philo;

	philo = (t_plst *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->info->meal_check);
		if (philo->info->die_flg || philo->info->all_ate)
			break ;
		if (check_all_ate(philo))
			break ;
		if (check_limit(philo))
			break ;
		pthread_mutex_unlock(&philo->info->meal_check);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	return (NULL);
}

void	*one_philosopher(t_plst *philo)
{
	put_message(get_time(), philo->id, GET_FORK);
	adjustment_sleep(get_time() + philo->info->death_time);
	put_message(get_time(), philo->id, TYPE_DIED);
	return (NULL);
}

void	*philosopher(void *void_philo)
{
	pthread_t	tid;
	t_plst		*philo;

	philo = (t_plst *)void_philo;
	if (philo->info->philo_num == 1)
		return (one_philosopher(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	if (pthread_create(&tid, NULL, monitor, void_philo) != 0)
		return (NULL);
	while (1)
	{
		if (get_forks(philo) == -1 \
		|| eat(philo) == -1 \
		|| put_forks(philo) == -1 \
		|| philo_sleep(philo) == -1 \
		|| think(philo) == -1)
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
