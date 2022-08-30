/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:06:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 14:08:03 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_free_share_sem(t_share *share)
{
	sem_unlink("sm_start");
	sem_close(share->sm_start);
	sem_unlink("sm_fork");
	sem_close(share->sm_fork);
	sem_unlink("sm_print");
	sem_close(share->sm_print);
	sem_unlink("sm_set_eat");
	sem_close(share->sm_set_eat);
	sem_unlink("sm_over_after");
	sem_close(share->sm_over_after);
	sem_unlink("sm_done");
	sem_close(share->sm_done);
}

void	ft_clear_simulating(t_share *share)
{
	t_philo			*philo;
	unsigned int	i;

	philo = share->philo;
	i = 0;
	while (i < share->info.num_philo)
	{
		unlink("sm_eat");
		sem_close(philo->sm_eat);
		i++;
	}
	ft_free_share_sem(share);
	ft_free((void **) &share->philo);
}

void	ft_term_all_process(t_philo *philo)
{
	unsigned int	i;
	t_share			*share;

	i = 0;
	share = philo->share;
	while (i < share->info.num_philo)
	{
		if (share->philo[i].pid > 0)
			kill(share->philo[i].pid, SIGTERM);
		i++;
	}
}

int	ft_stop_by_error(t_share *share, char *err_msg)
{
	ft_print_error(err_msg);
	ft_term_all_process(share->philo);
	ft_clear_simulating(share);
	return (EXIT_FAILURE);
}
