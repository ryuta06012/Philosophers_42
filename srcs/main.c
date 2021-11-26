/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:24:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 13:02:34 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor(void *void_philo)
{
	t_plst	*philo;

	philo = (t_plst *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->info->meal_check);
		if (philo->info->die_flg || philo->info->all_ate)
			break ;
		if (check_all_ate(philo))
			break ;
		if (check_limit(philo))
			break ;
		pthread_mutex_unlock(&philo->info->meal_check);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	return (NULL);
}

void	*philosopher(void *void_philo)
{
	pthread_t	tid;
	t_plst		*philo;

	philo = (t_plst *)void_philo;
	if (philo->id % 2 == 0)
		usleep(500);
	philo->t_last_meal = get_time();
	philo->limit = philo->t_last_meal + philo->info->death_time;
	if (pthread_create(&tid, NULL, monitor, (void *)void_philo) != 0)
		return (NULL);
	while (1)
	{
		if (get_forks(philo) == -1)
			break ;
		if (eat(philo) == -1)
			break ;
		if (put_forks(philo) == -1)
			break ;
		if (philo_sleep(philo) == -1)
			break ;
		if (think(philo) == -1)
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}

int	create_threads(t_plst *philo, int argc)
{
	int	i;
	int	philo_num;

	philo_num = philo->info->philo_num;
	i = 0;
	argc = 0;
	if (philo_num == 1)
	{
		put_message(get_time(), philo->id, GET_FORK);
		adjustment_sleep(get_time() + philo->info->death_time);
		put_message(get_time(), philo->id, TYPE_DIED);
		return (0);
	}
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
	if (philo_num == 1)
		return (0);
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
		return (-1);
	rules = init_rules(argv);
	philo = create_struct_philo(rules->philo_num);
	if (rules == NULL || philo == NULL)
		return (clear_philos_rules(philo, rules, -1));
	create_philo(philo, rules);
	if (create_threads(philo, argc) == -1)
		return (clear_philos_rules(philo, rules, -1));
	if (wait_end_threads(philo) == -1)
		return (clear_philos_rules(philo, rules, -1));
	clear_philos_rules(philo, rules, 0);
	return (0);
}
