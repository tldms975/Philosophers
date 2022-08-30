/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:56:52 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 21:41:24 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_right_fork(t_philo *a_philo)
{
	pthread_mutex_lock(&a_philo->share->m_over);
	if (a_philo->share->is_over)
	{
		pthread_mutex_unlock(&a_philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&a_philo->share->m_over);
	pthread_mutex_lock(a_philo->r_fork);
	a_philo->has_r_fork = ON;
	ft_print_state(a_philo, FORK);
}

static void	ft_take_left_fork(t_philo *a_philo)
{
	pthread_mutex_lock(&a_philo->share->m_over);
	if (a_philo->share->is_over)
	{
		if (a_philo->has_r_fork == ON)
		{
			pthread_mutex_unlock(a_philo->r_fork);
			a_philo->has_r_fork = OFF;
		}
		pthread_mutex_unlock(&a_philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&a_philo->share->m_over);
	if ((a_philo->share->info.num_philo == 1) && (a_philo->id == 1))
	{
		pthread_mutex_unlock(a_philo->r_fork);
		ft_usleep(a_philo->share->info.time_die);
	}
	else
	{
		pthread_mutex_lock(a_philo->l_fork);
		a_philo->has_l_fork = ON;
		ft_print_state(a_philo, FORK);
	}
}

static void	ft_choose_forks(t_philo *a_philo)
{
	if (a_philo->id % 2)
	{
		ft_take_right_fork(a_philo);
		ft_take_left_fork(a_philo);
	}
	else
	{
		ft_take_left_fork(a_philo);
		ft_take_right_fork(a_philo);
	}
}

void	ft_take_forks(t_philo *a_philo)
{
	ft_choose_forks(a_philo);
	pthread_mutex_lock(&a_philo->share->m_over);
	if (a_philo->share->is_over)
	{
		if (a_philo->has_r_fork == ON)
		{
			pthread_mutex_unlock(a_philo->r_fork);
			a_philo->has_r_fork = OFF;
		}
		if (a_philo->has_l_fork == ON)
		{
			pthread_mutex_unlock(a_philo->l_fork);
			a_philo->has_l_fork = OFF;
		}
		pthread_mutex_unlock(&a_philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&a_philo->share->m_over);
}
