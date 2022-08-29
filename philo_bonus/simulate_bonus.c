/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:46:39 by sielee            #+#    #+#             */
/*   Updated: 2022/08/29 16:11:47 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_simulate(t_share *share)
{
	unsigned int	i;

	i = 0;
	sem_wait(share->sm_start);
	share->start_time = ft_get_time_in_ms();
	while (i < share->info.num_philo)
	{
		share->philo[i].pid = fork();
		if (share->philo[i].pid == 0)
		{
			ft_philo_routine(&share->philo[i]);
			return (EXIT_SUCCESS);
		}
		if (share->philo[i].pid < 0)
			return (ft_stop_by_error(share, "fork error"));
		i++;
	}
	sem_post(share->sm_start);
	ft_monitoring_in_parent(share);
	ft_clear_simulating(share);
	return (EXIT_SUCCESS);
}
