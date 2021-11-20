/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_and_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 06:01:46 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/16 03:51:47 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	adjustment_sleep(long long after_time)
{
	long long	now;

	while (1)
	{
		now = get_time();
		if (now >= after_time)
		{
			break ;
		}
	}
}

int	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);
	}
	//pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_unlock(&philo->info->meal_check);
	put_message(get_time(), philo->id, TYPE_SLEEP);
	adjustment_sleep(get_time() + philo->info->sleep_time);
	return (0);
}

int	think(t_philos *philo)
{
	pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);
	}
	//pthread_mutex_unlock(&philo->info->meal_check);
	put_message(get_time(), philo->id, TYPE_THINK);
	pthread_mutex_unlock(&philo->info->meal_check);
	return (0);
}
