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

int	philo_sleep(t_philos *philo)
{
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
			return (-1);
	put_message(get_time(), philo->id, TYPE_SLEEP);
	usleep(philo->info->sleep_time * 1000);
	return (0);
}

int	think(t_philos *philo)
{
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
			return (-1);
	put_message(get_time(), philo->id, TYPE_THINK);
	return (0);
}
