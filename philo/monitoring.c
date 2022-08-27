/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:33:21 by sielee            #+#    #+#             */
/*   Updated: 2022/08/28 02:13:35 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_check_all_done(t_philo *philo)
{
	t_info			*info;
	unsigned int	i;

	info = &philo->share->info;
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&philo[i].monitor);
		if (philo[i].meal_cnt < info->num_must_eat)
		{
			pthread_mutex_unlock(&philo[i].monitor);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo[i].monitor);
		i++;
	}
	if (!philo->share->is_over)
		ft_print_done(philo);
	pthread_mutex_lock(&philo->share->m_over);
	philo->share->is_over = TRUE;
	pthread_mutex_unlock(&philo->share->m_over);
	return (TRUE);
}

static t_bool	ft_check_dead(t_philo *philo)
{
	t_info			*info;
	long long		starving;

	info = &philo->share->info;
	starving = 0;
	starving = ft_get_time_stamp(philo->last_meal);
	if (philo->meal_cnt == 0)
		starving = ft_get_time_stamp(philo->share->start_time);
	if (starving < info->time_die)
		return (FALSE);
	else
	{
		if (!philo->share->is_over)
			ft_print_die(philo);
		pthread_mutex_lock(&philo->share->m_over);
		philo->share->is_over = TRUE;
		pthread_mutex_unlock(&philo->share->m_over);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_monitoring(t_share *share)
{
	t_bool			is_dead;
	t_bool			is_all_done;
	unsigned int	i;

	is_dead = FALSE;
	is_all_done = FALSE;
	while (TRUE)
	{
		i = 0;
		while ((i < share->info.num_philo) && (!is_dead))
		{
			pthread_mutex_lock(&share->philo[i].monitor);
			is_dead = ft_check_dead(&share->philo[i]);
			pthread_mutex_unlock(&share->philo[i].monitor);
			i++;
		}
		if (share->info.num_must_eat)
			is_all_done = ft_check_all_done(share->philo);
		if (is_dead || is_all_done)
			break ;
	}
}
