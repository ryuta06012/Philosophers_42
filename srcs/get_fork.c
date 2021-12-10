/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:33:38 by hryuuta           #+#    #+#             */
/*   Updated: 2021/12/06 07:54:21 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_left_fork(t_plst *philo)
{
	int	lfork;

	lfork = philo->left_fork_id;
	pthread_mutex_lock(&philo->info->m_fork[lfork]);
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, FORK) == -1)
	{
		pthread_mutex_unlock(&philo->info->m_fork[lfork]);
		return (-1);
	}
	put_message(get_time(), philo->id, GET_FORK);
	pthread_mutex_unlock(&philo->info->meal_check);
	return (0);
}

int	get_right_fork(t_plst *philo)
{
	int	rfork;

	rfork = philo->right_fork_id;
	pthread_mutex_lock(&philo->info->m_fork[rfork]);
	pthread_mutex_lock(&philo->info->meal_check);
	if (ate_dieflg_check(philo, FORK) == -1)
	{
		pthread_mutex_unlock(&philo->info->m_fork[rfork]);
		return (-1);
	}
	put_message(get_time(), philo->id, GET_FORK);
	pthread_mutex_unlock(&philo->info->meal_check);
	return (0);
}

int	get_forks(t_plst *philo)
{
	if (get_left_fork(philo) == -1)
		return (-1);
	if (get_right_fork(philo) == -1)
	{
		pthread_mutex_unlock(&(philo->info->m_fork[philo->left_fork_id]));
		return (-1);
	}
	return (0);
}
