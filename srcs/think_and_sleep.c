/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_and_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 06:01:46 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 11:40:56 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	adjustment_sleep(long long end)
{
	long long	now;

	while (1)
	{
		now = get_time();
		if (now >= end)
			break ;
		usleep(1000);
	}
}

int	philo_sleep(t_plst *philo)
{
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, SLEEP) == -1)
		return (-1);
	put_message(get_time(), philo->id, TYPE_SLEEP);
	pthread_mutex_unlock(&philo->info->meal_check);
	adjustment_sleep(get_time() + philo->info->sleep_time);
	return (0);
}

int	think(t_plst *philo)
{
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, THINK) == -1)
		return (-1);
	put_message(get_time(), philo->id, TYPE_THINK);
	pthread_mutex_unlock(&philo->info->meal_check);
	return (0);
}
