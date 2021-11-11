/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:34:23 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/10 03:46:59 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	put_forks(t_philos *philo)
{
	int	lfork;
	int	rfork;

	lfork = philo->left_fork_id;
	rfork = philo->right_fork_id;
	pthread_mutex_unlock(&(philo->info->m_fork[lfork]));
	pthread_mutex_unlock(&(philo->info->m_fork[rfork]));
}
