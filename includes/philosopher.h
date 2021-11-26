/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:39:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/25 12:59:21 by hryuuta          ###   ########.fr       */
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

# define GET_FORK "has taken a fork"
# define TYPE_EAT "is eating"
# define TYPE_SLEEP "is sleeping"
# define TYPE_THINK "is thinking"
# define TYPE_DIED "died"

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

typedef struct s_plst
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
	struct s_plst		*left;
	struct s_plst		*right;
	pthread_t	thread_id;
}			t_plst;

enum {
	EAT,
	FORK,
	THINK,
	SLEEP
};

int	ft_atoi(const char *str);

/* set_up.c */
t_rules	*init_rules(char **argv);
t_plst	*init_philo(void);
t_plst	*create_struct_philo(int philo_num);
int		init_mutex(t_rules *rules);
void	create_philo(t_plst *philo, t_rules *rules);

/* eat.c */
int	ate_dieflg_check(t_plst *philo, int type);
int	eat(t_plst *philo);

/* get_fork */
int	get_left_fork(t_plst *philo);
int	get_right_fork(t_plst *philo);
int	get_forks(t_plst *philo);

/* put_forks */
int	put_forks(t_plst *philo);

/* put_message */
char	*get_message(int type);
void	put_message(long time, int philo_id, char *type);

/* think_sleep.c */
void	adjustment_sleep(long long after_time);
int		philo_sleep(t_plst *philo);
int		think(t_plst *philo);

/* exit.c */
void	clear_rules(t_rules *rules);
void			clear_philos(t_plst *philos);

/* utils.c */
long long	get_time(void);
int	clear_philos_rules(t_plst *philo, t_rules *rules, int status);
int	check_all_ate(t_plst *philo);
int	check_limit(t_plst *philo);

/* validate.c */
bool	check_argument(int argc, char **argv);
bool	check_digit(int argc, char **argv);
bool	ph_isdigit(char *arg);

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
