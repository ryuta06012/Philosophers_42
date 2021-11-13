/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:05 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/12 16:00:19 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->t_last_meal = get_time();
	put_message(philo->t_last_meal, philo->id, TYPE_EAT);
	usleep(philo->info->eat_time * 1000);
	philo->ate_count += 1;
	printf("id = %d, philo->ate_count = %d\n", philo->id, philo->ate_count);
	//printf("ate_num = %d\n", philo->info->ate_num);
	//printf("info->philo_num = %d\n", philo->info->philo_num);
	if (philo->ate_count == philo->info->ate_num)
	{
		printf("philo->ate_count = %d\n", philo->ate_count);
		pthread_mutex_lock(&philo->info->meal_check);
		philo->info->ate += 1;
		pthread_mutex_unlock(&philo->info->meal_check);
	}
	pthread_mutex_unlock(&philo->mutex);
}
