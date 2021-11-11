/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:44:56 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/10 06:48:44 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_rules	*init_rules(char **argv)
{
	t_rules		*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (rules->philo_num + 1));
	rules->all_ate = 0;
	rules->eat_num = 0;
	rules->die_flg = 0;
	rules->first_timestamp = 0;
	return (rules);
}

t_philos	*init_philo(void)
{
	t_philos	*philo;

	philo = (t_philos *)malloc(sizeof(t_philos));
	philo->right = philo;
	philo->left = philo;
	return (philo);
}

t_philos	*create_struct_philo(int philo_num)
{
	t_philos	*philo;
	t_philos	*new;

	philo = init_philo();
	philo_num -= 1;
	while (philo_num--)
	{
		new = (t_philos *)malloc(sizeof(t_philos));
		philo->right->left = new;
		new->right = philo->right;
		new->left = philo;
		philo->right = new;
	}
	return (philo);
}

int	init_mutex(t_rules *rules)
{
	int	num;

	num =  rules->philo_num;
	while (--num >= 0)
	{
		pthread_mutex_init(&(rules->m_fork[num]), NULL);
	}
	pthread_mutex_init(&rules->meal_check, NULL);
	return (0);
}

void	create_philo(t_philos *philo, t_rules *rules)
{
	int	i;

	i = 0;
	init_mutex(rules);
	while (i < rules->philo_num)
	{
		philo->id = i;
		philo->is_eat = 0;
		philo->t_last_meal = 0;
		philo->limit = 0;
		philo->info = rules;
		pthread_mutex_init(&(philo->mutex), NULL);
		philo->right_fork_id = i;
		philo->left_fork_id = (i + 1) % rules->philo_num;
		i++;
		philo = philo->left;
	}
}
