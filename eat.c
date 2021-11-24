/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:05 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/24 12:28:01 by hryuuta          ###   ########.fr       */
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
	//eattime_set(philo);
	//eattime_set(philo);
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, TYPE_EAT) == -1)
		return (-1);
	eattime_set(philo);
	put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	pthread_mutex_unlock(&philo->info->meal_check);
	//put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	//eattime_set(philo);
	adjustment_sleep(get_time() + philo->info->eat_time);
	return (0);
}
