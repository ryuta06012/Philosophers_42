/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 03:43:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/17 03:02:00 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating");
	else if (type == TYPE_LFORK)
		return (" took a left_fork ");
	else if (type == TYPE_RFORK)
		return (" took a right_fork ");
	else if (type == TYPE_SLEEP)
		return (" is sleeping");
	else if (type == TYPE_THINK)
		return (" is thinking");
	else if (type == TYPE_ORVER)
		return ("time orver");
	return ("died");
}

void	put_message(long time, int philo_id, int type)
{
	printf("%ld %d %s\n", time, philo_id, get_message(type));
}
