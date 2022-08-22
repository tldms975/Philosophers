/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:35:48 by sielee            #+#    #+#             */
/*   Updated: 2022/08/23 03:31:11 by sielee           ###   ########seoul.kr  */
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
typedef struct s_play	t_play;
typedef struct timeval	t_timeval;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pthread;
typedef enum e_state	t_state;


int		ft_atoi(const char *str);
void	*ft_malloc(size_t size);

void	ft_free(void **ptr);
void	ft_free_philo(t_philo *philo);

void	ft_error(char *str);
int		ft_end_with_free(t_philo *philo, char *err_msg);

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

struct s_info
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_must_eat;
};

struct s_philo
{
	struct s_philo	*left;
	struct s_philo	*right;
	t_info			*info;
	t_mutex			*mutex;
	t_pthread		tid;
	int				id;
	int				meal_cnt;
};

struct s_play
{
	t_philo	*philo;
	t_info	*info;
};

#endif