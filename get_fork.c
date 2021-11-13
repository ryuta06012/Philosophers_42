/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:33:38 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/13 23:19:52 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	get_left_fork(t_philos *philo)
{
	int	lfork;

	lfork = philo->left_fork_id;
	pthread_mutex_lock(&philo->info->m_fork[lfork]);
	put_message(get_time(), philo->id, TYPE_LFORK);
}

void	get_right_fork(t_philos *philo)
{
	int	rfork;

	rfork = philo->right_fork_id;
	pthread_mutex_lock(&philo->info->m_fork[rfork]);
	put_message(get_time(), philo->id, TYPE_RFORK);
}

void	get_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		get_left_fork(philo);
		get_right_fork(philo);
	}
	else
	{
		get_right_fork(philo);
		get_left_fork(philo);
	}
}
