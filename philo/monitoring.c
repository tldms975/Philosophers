/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:33:21 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 22:04:34 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_sign	ft_check_all_done(t_philo *philo)
{
	t_info			*info;
	unsigned int	i;

	info = &philo->share->info;
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_lock(&philo[i].m_eat);
		if (philo[i].meal_cnt < info->num_must_eat)
		{
			pthread_mutex_unlock(&philo[i].m_eat);
			return (FALSE);
		}
		pthread_mutex_unlock(&philo[i].m_eat);
		i++;
	}
	if (!philo->share->is_over)
	{
		ft_print_done(philo);
		return (TRUE);
	}
	return (FALSE);
}

static t_sign	ft_check_dead(t_philo *philo)
{
	t_info			*info;
	long long		starving;

	info = &philo->share->info;
	pthread_mutex_lock(&philo->m_eat);
	if (philo->meal_cnt != 0)
		starving = ft_get_time_stamp(philo->last_meal);
	else
		starving = ft_get_time_stamp(philo->share->start_time);
	pthread_mutex_unlock(&philo->m_eat);
	if (starving < info->time_die)
		return (FALSE);
	else if (!philo->share->is_over)
	{
		printf("timd die: %u\n", info->time_die);
		printf("starving: %llu\n", starving);
		ft_print_die(philo);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_monitoring(t_share *share)
{
	unsigned int	i;
	t_sign			is_dead;

	while (TRUE)
	{
		i = 0;
		while ((i < share->info.num_philo) && (!is_dead))
		{
			is_dead = ft_check_dead(&share->philo[i]);
			i++;
		}
		if (is_dead)
			break ;
		if (share->info.num_must_eat && ft_check_all_done(share->philo))
			break ;
	}
}
