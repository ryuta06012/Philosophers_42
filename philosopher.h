/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:39:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/10 06:23:11 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct		s_rules
{
	int		philo_num;
	int		death_time;
	int		eat_time;
	int		sleep_time;
	int		die_flg;
	int		eat_num;
	int		all_ate;
	long long	first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		*m_fork;
}		t_rules;

typedef struct		s_philos
{
	int		id;
	int		is_eat;
	int		left_fork_id;
	int		right_fork_id;
	long long	t_last_meal;
	long long	limit;
	t_rules		*info;
	pthread_mutex_t		mutex;
	struct s_philos		*left;
	struct s_philos		*right;
	pthread_t	thread_id;
}			t_philos;

enum
{
	TYPE_SLEEP,
	TYPE_EAT,
	TYPE_THINK,
	TYPE_LFORK,
	TYPE_RFORK,
	TYPE_DIED,
	TYPE_ORVER,
};

int	ft_atoi(const char *str);
long long	get_time(void);

/* set_up.c */
t_rules	*init_rules(char **argv);
t_philos	*init_philo(void);
t_philos	*create_struct_philo(int philo_num);
int	init_mutex(t_rules *rules);
void	create_philo(t_philos *philo, t_rules *rules);

/* eat.c */
void	eat(t_philos *philo);

/* get_fork */
void	get_left_fork(t_philos *philo);
void	get_right_fork(t_philos *philo);
void	get_forks(t_philos *philo);

/* put_forks */
void	put_forks(t_philos *philo);

/* put_message */
char	*get_message(int type);
void	put_message(long time, int philo_id, int type);

/* think_sleep.c */
void	philo_sleep(t_philos *philo);
void	think(t_philos *philo);

#endif
