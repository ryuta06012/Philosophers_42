/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:30:52 by hryuuta           #+#    #+#             */
/*   Updated: 2021/12/06 04:54:37 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	clear_philos_rules(t_plst *philo, t_rules *rules, int status)
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

int	check_all_ate(t_plst *philo)
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

int	check_limit(t_plst *philo)
{
	if (get_time() >= philo->limit)
	{
		philo->info->die_flg = 1;
		put_message(get_time(), philo->id, TYPE_DIED);
		return (1);
	}
	return (0);
}

void	ph_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
