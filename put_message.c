/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 03:43:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/24 12:21:45 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return ("is eating");
	else if (type == TYPE_LFORK)
		return ("has taken a fork");
	else if (type == TYPE_RFORK)
		return ("has taken a fork");
	else if (type == TYPE_SLEEP)
		return ("is sleeping");
	else if (type == TYPE_THINK)
		return ("is thinking");
	else if (type == TYPE_ORVER)
		return ("time orver");
	return ("died");
}

void	put_message(long time, int philo_id, int type)
{
	//pthread_mutex_lock(&philo->info->meal_check);
	printf("%ld %d %s\n", time, philo_id, get_message(type));
	//pthread_mutex_unlock(&philo->info->meal_check);
}
