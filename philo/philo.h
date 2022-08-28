/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:35:48 by sielee            #+#    #+#             */
/*   Updated: 2022/08/28 16:24:12 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define COL_RED "\x1b[31m" 
# define COL_GREEN "\x1b[32m"
# define COL_ORIGIN "\x1b[0m"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct s_share	t_share;
typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pthread;
typedef enum e_state	t_state;
typedef enum e_sign		t_sign;

/* UTILS */
unsigned int	ft_atoui(const char *str);
t_sign			ft_if_valid_args_range(char *av[]);
size_t			ft_strlen(const char *s);
void			*ft_malloc(size_t size);
void			ft_free(void **ptr);
int				ft_print_error(char *str);

/* SIMULATION */
int				ft_simulate(t_share *share);
int				ft_init_share(t_share *round, char *av[]);
void			*ft_philo_routine(void *arg);
void			ft_take_forks(t_philo *a_philo);
void			ft_monitoring(t_share *share);

/* PRINT */
void			ft_print_state(t_philo *philo, t_state state);
void			ft_print_done(t_philo *philo);
void			ft_print_die(t_philo *philo);

/* TIME */
long long		ft_get_time_in_ms(void);
long long		ft_get_time_stamp(long long start_time);

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
};

enum e_sign
{
	FALSE = 0,
	TRUE = 1,
	ERR = 2,
	OFF = 0,
	ON = 1
};

struct s_info
{
	unsigned int	num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	num_must_eat;
};

struct s_philo
{
	t_pthread		tid;
	t_mutex			monitor;
	t_mutex			fork;
	t_mutex			*r_fork;
	t_mutex			*l_fork;
	t_sign			has_r_fork;
	t_sign			has_l_fork;
	t_share			*share;
	unsigned int	id;
	unsigned int	meal_cnt;
	long long		last_meal;
};

struct s_share
{
	t_philo			*philo;
	t_info			info;
	t_mutex			m_ready;
	t_mutex			m_print;
	t_mutex			m_over;
	long long		start_time;
	t_sign			is_over;
	t_sign			is_ready;
};

#endif