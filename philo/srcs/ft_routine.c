/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:45:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/25 16:29:06 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	ft_print_state(philo, FORK);
	ft_print_state(philo, EAT);
	usleep(philo->info->time_eat * 1000);
	philo->meal_cnt += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_wait_others(t_mutex *mut_ready)
{
	pthread_mutex_lock(mut_ready);
	pthread_mutex_unlock(mut_ready);
}

void	ft_think(t_philo *philo)
{
	ft_print_state(philo, THINK);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_state(philo, SLEEP);
	usleep(philo->info->time_sleep * 1000);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	// while (!((one_philo->id == one_philo->info->num_philo - 1) && \
	// (one_philo->meal_cnt == one_philo->info->num_must_eat)))
	{
		//ft_wait_others(one_philo->share);
		ft_eat(one_philo);
		ft_sleep(one_philo);
		ft_think(one_philo);
	}
	return (NULL);
}
