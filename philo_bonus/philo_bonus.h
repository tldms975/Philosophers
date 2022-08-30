/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:35:48 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 15:08:47 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define COL_RED "\x1b[31m" 
# define COL_GREEN "\x1b[32m"
# define COL_ORIGIN "\x1b[0m"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct s_share	t_share;
typedef struct timeval	t_timeval;
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
int				ft_init_share(t_share *share, char *av[]);
int				ft_simulate(t_share *share);
void			ft_philo_routine(t_philo *a_philo);
void			ft_monitoring_in_each_philo(t_philo *a_philo);
void			ft_monitoring_in_parent(t_share *share);
void			ft_term_all_process(t_philo *philo);

/* PRINT */
void			ft_print_state(t_philo *philo, t_state state);
void			ft_print_die(t_philo *philo);
void			ft_print_done(t_philo *philo);

/* TIME */
long long		ft_get_time_in_ms(void);
long long		ft_get_time_stamp(long long start_time);
void			ft_usleep(long long time);

/* TERMINATE */
int				ft_stop_by_error(t_share *share, char *err_msg);
void			ft_clear_simulating(t_share *share);
void			ft_term_all_process(t_philo *philo);

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
	unsigned int	id;
	pid_t			pid;
	pthread_t		tid;
	sem_t			*sm_eat;
	t_share			*share;
	unsigned int	meal_cnt;
	long long		last_meal;
};

struct s_share
{
	t_philo			*philo;
	t_info			info;
	sem_t			*sm_start;
	sem_t			*sm_print;
	sem_t			*sm_fork;
	sem_t			*sm_set_eat;
	sem_t			*sm_done;
	sem_t			*sm_over_after;
	t_sign			is_dead;
	long long		start_time;
};

#endif