/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_and_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 06:01:46 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/10 06:01:57 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_sleep(t_philos *philo)
{
	usleep(philo->info->sleep_time);
	put_message(get_time(), philo->id, TYPE_SLEEP);
}

void	think(t_philos *philo)
{
	put_message(get_time(), philo->id, TYPE_THINK);
}
