/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:35:48 by sielee            #+#    #+#             */
/*   Updated: 2022/08/24 20:26:36 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct s_round	t_round;
typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pthread;
typedef enum e_state	t_state;
typedef enum e_bool		t_bool;

unsigned int	ft_atoui(const char *str);
t_bool			ft_if_valid_args_range(char *av[]);
size_t			ft_strlen(const char *s);
void			*ft_malloc(size_t size);

void			ft_free(void **ptr);
void			ft_free_philo(t_philo *philo);

int				ft_print_error(char *str);
int				ft_end_with_free(t_philo *philo, char *err_msg);

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

enum e_bool
{
	OFF = 0,
	ON = 1,
	FALSE = 0,
	TRUE = 1
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
	t_info		*info;
	t_mutex		mut_eat;
	t_pthread	tid;
	t_bool		fork;
	t_bool		*l_fork;
	t_bool		*r_fork;
	int			id;
	int			meal_cnt;
};

struct s_round
{
	t_philo	*philo;
	t_info	*info;
};

#endif