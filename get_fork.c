/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:33:38 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/16 03:52:55 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_left_fork(t_philos *philo)
{
	int	lfork;

	lfork = philo->left_fork_id;
	//printf("-------l1---------------%d\n", philo->id);
	pthread_mutex_lock(&philo->info->meal_check);
	//printf("-------l2---------------%d\n", philo->id);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		//printf("-----left_fork_erro-----\n");
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);	
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	pthread_mutex_lock(&philo->info->m_fork[lfork]);
	put_message(get_time(), philo->id, TYPE_LFORK);
	//printf("-------l4---------------%d\n", philo->id);
	//pthread_mutex_lock(&philo->info->m_fork[lfork]);
	//printf("-------l5---------------%d\n", philo->id);
	//put_message(get_time(), philo->id, TYPE_LFORK);
	//printf("-------l6---------------%d\n", philo->id);
	return (0);
}

int	get_right_fork(t_philos *philo)
{
	int	rfork;

	rfork = philo->right_fork_id;
	//printf("-------r1--------------- %d\n", philo->id);
	pthread_mutex_lock(&philo->info->meal_check);
	//printf("-------r2---------------%d\n", philo->id);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		//printf("-----right_fork_erro-----\n");
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->meal_check);
		pthread_mutex_lock(&philo->info->m_fork[rfork]);
		put_message(get_time(), philo->id, TYPE_RFORK);
	}
	//printf("-------r3---------------%d\n", philo->id);
	//pthread_mutex_unlock(&philo->info->meal_check);
	//pthread_mutex_lock(&philo->info->m_fork[rfork]);
	//pthread_mutex_lock(&philo->info->m_fork[rfork]);
	//put_message(get_time(), philo->id, TYPE_RFORK);
	//printf("-------r4---------------%d\n", philo->id);
	//pthread_mutex_lock(&philo->info->m_fork[rfork]);
	//printf("-------r5---------------%d\n", philo->id);
	//put_message(get_time(), philo->id, TYPE_RFORK);
	//printf("-------r6---------------%d\n", philo->id);
	return (0);
}

int	get_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->info->meal_check);
	if (philo->info->all_ate == 1 || philo->info->die_flg == 1)
	{
		pthread_mutex_unlock(&philo->info->meal_check);
		return (-1);
	}
	pthread_mutex_unlock(&philo->info->meal_check);
	/* if (get_left_fork(philo) == -1)
	{
			//printf("--------erro_get_left_fork------\n");
			return (-1);
	}
	//printf("---------b-------\n");
	if (get_right_fork(philo) == -1)
	{
			printf("--------erro_get_right_fork------\n");
			pthread_mutex_unlock(&(philo->info->m_fork[philo->left_fork_id]));
			return (-1);
	} */
	//printf("----------a------\n");
	if (philo->id % 2 == 0)
	{
		//printf("---------1-------\n");
		if (get_left_fork(philo) == -1)
		{
			//printf("--------erro_get_left_fork------\n");
			return (-1);
		}
		//printf("---------b-------\n");
		if (get_right_fork(philo) == -1)
		{
			printf("--------erro_get_right_fork------\n");
			pthread_mutex_unlock(&(philo->info->m_fork[philo->left_fork_id]));
			return (-1);
		}
		//printf("---------d-------\n");
	}
	else
	{
		//printf("---------2-------\n");
		if (get_right_fork(philo) == -1)
		{
			//printf("--------erro_get_right_fork------\n");
			return (-1);
		}
		//printf("---------3-------\n");
		if (get_left_fork(philo) == -1)
		{
			printf("--------erro_get_left_fork------\n");
			pthread_mutex_unlock(&(philo->info->m_fork[philo->right_fork_id]));
			return (-1);
		}
		//printf("---------5-------\n");
	}
	return (0);
}
