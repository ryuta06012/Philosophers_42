/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:05 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/23 11:03:21 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ate_dieflg_check(t_philos *philo, int type)
{
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		if (type == TYPE_EAT)
		{
			put_forks(philo);
			pthread_mutex_unlock(&philo->info->meal_check);
			//pthread_mutex_unlock(&philo->mutex);
			return (-1);
		}
		else
		{
			pthread_mutex_unlock(&philo->info->meal_check);
			return (-1);
		}
	}
	return (0);
}

void	eattime_set(t_philos *philo)
{
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
}

int	eat(t_philos *philo)
{
	//pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, TYPE_EAT) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_lock(&philo->info->meal_check);
	eattime_set(philo);
	pthread_mutex_unlock(&philo->info->meal_check);
	put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	pthread_mutex_lock(&philo->info->meal_check);
	philo->ate_count += 1;
	if (philo->ate_count == philo->info->ate_num)
		philo->info->ate += 1;
	pthread_mutex_unlock(&philo->info->meal_check);
	adjustment_sleep(philo->t_last_meal + philo->info->eat_time);
	/* pthread_mutex_lock(&philo->info->meal_check);
	philo->ate_count += 1;
	if (philo->ate_count == philo->info->ate_num)
		philo->info->ate += 1;
	pthread_mutex_unlock(&philo->info->meal_check); */
	//pthread_mutex_unlock(&philo->mutex);
	return (0);
}
