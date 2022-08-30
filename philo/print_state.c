/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:28:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 14:17:33 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->m_print);
	pthread_mutex_lock(&philo->share->m_over);
	if (philo->share->is_over)
	{
		pthread_mutex_unlock(&philo->share->m_over);
		pthread_mutex_unlock(&philo->share->m_print);
		return ;
	}
	philo->share->is_over = TRUE;
	pthread_mutex_unlock(&philo->share->m_over);
	printf(COL_GREEN "Simulation stopped successfully!\n" COL_ORIGIN);
	pthread_mutex_unlock(&philo->share->m_print);
}

void	ft_print_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->m_print);
	pthread_mutex_lock(&philo->share->m_over);
	if (philo->share->is_over)
	{
		pthread_mutex_unlock(&philo->share->m_over);
		pthread_mutex_unlock(&philo->share->m_print);
		return ;
	}
	philo->share->is_over = TRUE;
	pthread_mutex_unlock(&philo->share->m_over);
	printf(COL_RED "%lld ms\t%d died\n" COL_ORIGIN, \
	ft_get_time_stamp(philo->share->start_time), philo->id);
	pthread_mutex_unlock(&philo->share->m_print);
}

void	ft_print_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->share->m_print);
	pthread_mutex_lock(&philo->share->m_over);
	if (philo->share->is_over)
	{
		pthread_mutex_unlock(&philo->share->m_over);
		pthread_mutex_unlock(&philo->share->m_print);
		if (state == EAT)
			pthread_mutex_unlock(&philo->monitor);
		return ;
	}
	pthread_mutex_unlock(&philo->share->m_over);
	printf("%lld ms\t%d ", ft_get_time_stamp(philo->share->start_time), \
	philo->id);
	if (state == FORK)
		printf("has taken a fork\n");
	else if (state == EAT)
		printf("is eating\n");
	else if (state == SLEEP)
		printf("is sleeping\n");
	else if (state == THINK)
		printf("is thinking\n");
	pthread_mutex_unlock(&philo->share->m_print);
}
