/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/12/06 07:51:13 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdlib.h>

int	create_threads(t_plst *philo)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&(philo->thread_id), NULL, \
		philosopher, (void *)philo) != 0)
			return (-1);
		philo = philo->left;
		i++;
	}
	return (0);
}

int	wait_end_threads(t_plst *philo)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	while (i < philo_num)
	{
		if (pthread_join(philo->thread_id, NULL) != 0)
			return (-1);
		philo = philo->left;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_plst		*philo;
	t_rules		*rules;

	if (check_argument(argc, argv) == false)
	{
		ph_putendl_fd("error: bad argument!", 2);
		return (-1);
	}
	rules = init_rules(argv);
	philo = create_struct_philo(rules->philo_num);
	if (rules == NULL || philo == NULL)
		return (clear_philos_rules(philo, rules, -1));
	create_philo(philo, rules);
	if (create_threads(philo) == -1)
		return (clear_philos_rules(philo, rules, -1));
	if (wait_end_threads(philo) == -1)
		return (clear_philos_rules(philo, rules, -1));
	clear_philos_rules(philo, rules, 0);
	return (0);
}
