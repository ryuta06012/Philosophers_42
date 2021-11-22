/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:30:52 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/22 12:31:40 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	clear_philos_rules(t_philos *philo, t_rules *rules, int status)
{
	clear_philos(philo);
	clear_rules(rules);
	return (status);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_eat_count(t_philos *philo)
{
	int		ate_count;

	ate_count = philo->info->ate;
	if (ate_count && ate_count == philo->info->philo_num)
	{
		philo->info->all_ate = 1;
		return (1);
	}
	return (0);
}

int	check_limit(t_philos *philo)
{
	if (get_time() >= philo->limit)
	{
		philo->info->die_flg = 1;
		put_message(get_time(), philo->id, TYPE_DIED);
		return (1);
	}
	return (0);
}
