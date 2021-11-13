/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 06:50:09 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/13 23:18:55 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clear_rules(t_rules *rules)
{
	int	i;
	
	if (rules->m_fork)
	{	
		i = 0;
		while (i < rules->philo_num)
			pthread_mutex_destroy(&rules->m_fork[i++]);
		free(rules->m_fork);
		//rules->m_fork = NULL;
	}
	pthread_mutex_destroy(&rules->meal_check);
	pthread_mutex_destroy(&rules->mutex);
	free(rules);
}

void	clear_philos(t_philos *philos)
{
	int		i;
	int		philo_num;
	t_philos	*tmp;

	i = 0;
	philo_num = philos->info->philo_num;
	while (i++ < philo_num)
	{
		tmp = philos->left;
		pthread_mutex_destroy(&(philos->mutex));
		free(philos);
		philos = tmp;
	}
}

