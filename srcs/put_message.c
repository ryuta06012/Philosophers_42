/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 03:43:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/12/06 07:50:09 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	put_message(long time, int philo_id, char *type)
{
	printf("%ld %d %s\n", time, philo_id, type);
}
