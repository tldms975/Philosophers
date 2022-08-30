/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:45:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 17:54:25 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *a_philo)
{
	if (a_philo->has_r_fork && a_philo->has_l_fork)
	{
		pthread_mutex_lock(&a_philo->monitor);
		ft_print_state(a_philo, EAT);
		a_philo->last_meal = ft_get_time_in_ms();
		a_philo->meal_cnt += 1;
		ft_usleep(a_philo->share->info.time_eat);
		pthread_mutex_unlock(a_philo->r_fork);
		a_philo->has_r_fork = OFF;
		pthread_mutex_unlock(a_philo->l_fork);
		a_philo->has_l_fork = OFF;
		pthread_mutex_unlock(&a_philo->monitor);
	}
}

static void	ft_sleep_and_think(t_philo *a_philo)
{
	pthread_mutex_lock(&a_philo->share->m_over);
	if (a_philo->share->is_over)
	{
		pthread_mutex_unlock(&a_philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&a_philo->share->m_over);
	ft_print_state(a_philo, SLEEP);
	ft_usleep(a_philo->share->info.time_sleep);
	pthread_mutex_lock(&a_philo->share->m_over);
	if (a_philo->share->is_over)
	{
		pthread_mutex_unlock(&a_philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&a_philo->share->m_over);
	ft_print_state(a_philo, THINK);
	if (a_philo->share->info.num_philo % 2)
		usleep(100);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*a_philo;

	a_philo = (t_philo *)arg;
	pthread_mutex_lock(&a_philo->share->m_ready);
	pthread_mutex_unlock(&a_philo->share->m_ready);
	if (a_philo->share->is_ready == ERR)
		return (NULL);
	if (!(a_philo->id % 2))
		ft_usleep(a_philo->share->info.time_eat);
	while (TRUE)
	{
		ft_take_forks(a_philo);
		ft_eat(a_philo);
		ft_sleep_and_think(a_philo);
		pthread_mutex_lock(&a_philo->share->m_over);
		if (a_philo->share->is_over)
		{
			pthread_mutex_unlock(&a_philo->share->m_over);
			break ;
		}
		pthread_mutex_unlock(&a_philo->share->m_over);
	}
	return (NULL);
}
