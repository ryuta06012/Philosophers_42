/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:05 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 11:40:55 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ate_dieflg_check(t_plst *philo, int type)
{
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		if (type == EAT)
			put_forks(philo);
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);
	}
	return (0);
}

void	eattime_set(t_plst *philo)
{
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
}

void	check_eat_count(t_plst *philo)
{
	if (philo->ate_count == philo->info->ate_num)
		philo->info->ate += 1;
}

int	eat(t_plst *philo)
{
	philo->ate_count += 1;
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, EAT) == -1)
		return (-1);
	eattime_set(philo);
	check_eat_count(philo);
	put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	pthread_mutex_unlock(&philo->info->meal_check);
	adjustment_sleep(get_time() + philo->info->eat_time);
	return (0);
}
