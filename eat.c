/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:05 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/10 06:48:21 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->t_last_meal = get_time();
	put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	philo->is_eat = 1;
	usleep(philo->info->eat_time);
	philo->is_eat = 0;
	pthread_mutex_lock(&philo->info->meal_check);
	philo->info->eat_num += 1;
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_unlock(&philo->mutex);
}
