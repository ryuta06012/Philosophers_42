/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:44:56 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/13 23:07:29 by hryuuta          ###   ########.fr       */
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
	if (argv[5] != NULL)
		rules->ate_num = ft_atoi(argv[5]);
	printf("rules->ate_num = %d\n", rules->ate_num);
	rules->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (rules->philo_num + 1));
	rules->die_flg = 0;
	rules->ate = 0;
	rules->all_ate = 0;
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
	pthread_mutex_init(&rules->mutex, NULL);
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
		philo->right_fork_id = i;
		philo->left_fork_id = (i + 1) % rules->philo_num;
		philo->ate_count = 0;
		philo->t_last_meal = 0;
		philo->limit = 0;
		philo->info = rules;
		printf("philo->info->ate_num = %d\n", philo->info->ate_num);
		printf("philo->info->death_time = %d\n", philo->info->death_time);
		printf("philo->info->eat_time = %d\n", philo->info->eat_time);
		pthread_mutex_init(&(philo->mutex), NULL);
		i++;
		philo = philo->left;
	}
}
