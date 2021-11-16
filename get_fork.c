/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:33:38 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/16 03:52:55 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_left_fork(t_philos *philo)
{
	int	lfork;

	lfork = philo->left_fork_id;
	pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
			return (-1);
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_lock(&philo->info->m_fork[lfork]);
	put_message(get_time(), philo->id, TYPE_LFORK);
	return (0);
}

int	get_right_fork(t_philos *philo)
{
	int	rfork;

	rfork = philo->right_fork_id;
	//pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
			return (-1);
	//pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_lock(&philo->info->m_fork[rfork]);
	put_message(get_time(), philo->id, TYPE_RFORK);
	return (0);
}

int	get_forks(t_philos *philo)
{
	//pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
			return (-1);
	//pthread_mutex_unlock(&philo->info->meal_check);
	if (philo->id % 2 == 0)
	{
		if (get_left_fork(philo) == -1)
			return (-1);
		if (get_right_fork(philo) == -1)
			return (-1);
	}
	else
	{
		if (get_right_fork(philo) == -1)
			return (-1);
		if (get_left_fork(philo) == -1)
			return (-1);
	}
	return (0);
}
