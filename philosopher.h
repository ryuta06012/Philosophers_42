/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:39:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 09:08:17 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_rules
{
	long long	first_timestamp;
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		meal_check;
	pthread_mutex_t	mutex;
	int			philo_num;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			ate_num;
	int			die_flg;
	int			ate;
	int			all_ate;
}		t_rules;

typedef struct s_philos
{
	int		id;
	int		is_eat;
	int		left_fork_id;
	int		right_fork_id;
	int		ate_count;
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
	TYPE_GETFORKS,
	TYPE_LFORK,
	TYPE_RFORK,
	TYPE_DIED,
	TYPE_ORVER,
};

int	ft_atoi(const char *str);

/* set_up.c */
t_rules	*init_rules(char **argv);
t_philos	*init_philo(void);
t_philos	*create_struct_philo(int philo_num);
int		init_mutex(t_rules *rules);
void	create_philo(t_philos *philo, t_rules *rules);

/* eat.c */
int	ate_dieflg_check(t_philos *philo, int type);
int	eat(t_philos *philo);

/* get_fork */
int	get_left_fork(t_philos *philo);
int	get_right_fork(t_philos *philo);
int	get_forks(t_philos *philo);

/* put_forks */
int	put_forks(t_philos *philo);

/* put_message */
char	*get_message(int type);
void	put_message(long time, int philo_id, int type);

/* think_sleep.c */
void	adjustment_sleep(long long after_time);
int		philo_sleep(t_philos *philo);
int		think(t_philos *philo);

/* exit.c */
void	clear_rules(t_rules *rules);
void			clear_philos(t_philos *philos);

/* utils.c */
long long	get_time(void);
int	clear_philos_rules(t_philos *philo, t_rules *rules, int status);
int	check_eat_count(t_philos *philo);
int	check_limit(t_philos *philo);
int	check_argument(int argc, char **argv);

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

#endif
