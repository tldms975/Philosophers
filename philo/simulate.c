/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:46:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 23:44:02 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_all(t_philo *philo, unsigned int idx_end)
{
	unsigned int	i;

	i = 0;
	while (i < idx_end)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}

static void	ft_stop_simulating(t_share *share, unsigned int idx_end)
{
	t_philo			*philo;
	unsigned int	i;

	philo = share->philo;
	i = 0;
	while (i < idx_end)
	{
		pthread_mutex_destroy(&philo[i].fork);
		pthread_mutex_destroy(&philo[i].m_eat);
		i++;
	}
	pthread_mutex_destroy(&share->m_ready);
	pthread_mutex_destroy(&share->m_print);
	pthread_mutex_destroy(&share->m_over);
	ft_free((void **) &share->philo);
}

static int	ft_stop_by_error(t_share *share, unsigned int idx_end, \
char *err_msg)
{
	ft_print_error(err_msg);
	if (idx_end > 0)
	{
		ft_wait_all(share->philo, idx_end - 1);
		ft_stop_simulating(share, idx_end - 1);
	}
	return (EXIT_FAILURE);
}

int	ft_simulate(t_share *share)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&share->m_ready);
	while (i < share->info.num_philo)
	{
		if (pthread_create(&share->philo[i].tid, NULL, \
		ft_philo_routine, (void *) &share->philo[i]))
		{
			share->is_ready = ERR;
			pthread_mutex_unlock(&share->m_ready);
			return (ft_stop_by_error(share, i, "error: pthread_create"));
		}
		i++;
	}
	share->start_time = ft_get_time_in_ms();
	pthread_mutex_unlock(&share->m_ready);
	ft_monitoring(share);
	ft_wait_all(share->philo, i);
	ft_stop_simulating(share, i);
	return (EXIT_SUCCESS);
}
