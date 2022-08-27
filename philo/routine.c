/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:45:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/27 15:19:42 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philo *a_philo)
{
	pthread_mutex_lock(a_philo->l_fork);
	pthread_mutex_lock(a_philo->r_fork);
	ft_print_state(a_philo, FORK);
	pthread_mutex_lock(&a_philo->monitor);
	ft_print_state(a_philo, EAT);
	a_philo->last_meal = ft_get_time_in_ms();
	usleep(a_philo->share->info.time_eat * 1e3);
	a_philo->meal_cnt += 1;
	pthread_mutex_unlock(&a_philo->monitor);
	pthread_mutex_unlock(a_philo->l_fork);
	pthread_mutex_unlock(a_philo->r_fork);
}

static void	ft_sleep_and_think(t_philo *a_philo)
{
	ft_print_state(a_philo, SLEEP);
	usleep(a_philo->share->info.time_sleep * 1e3);
	ft_print_state(a_philo, THINK);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*a_philo;

	a_philo = (t_philo *)arg;
	pthread_mutex_lock(&a_philo->share->all_ready);
	pthread_mutex_unlock(&a_philo->share->all_ready);
	while (TRUE)
	{
		pthread_mutex_lock(&a_philo->share->m_over);
		if (a_philo->share->is_over)
		{
			pthread_mutex_unlock(&a_philo->share->m_over);
			break ;
		}
		pthread_mutex_unlock(&a_philo->share->m_over);
		ft_eat(a_philo);
		ft_sleep_and_think(a_philo);
	}
	return (NULL);
}
