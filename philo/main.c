/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:52:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/27 17:04:04 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_all(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&philo->share->m_over);
	if (philo->share->is_over)
	{
		pthread_mutex_unlock(&philo->share->m_over);
		return ;
	}
	pthread_mutex_unlock(&philo->share->m_over);
	while (i < philo->share->info.num_philo)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}

static void	ft_stop_simulating(t_share *share)
{
	t_philo			*philo;
	unsigned int	i;

	philo = share->philo;
	i = 0;
	while (i < share->info.num_philo)
	{
		pthread_mutex_destroy(&philo[i].fork);
		pthread_mutex_destroy(&philo[i].monitor);
		i++;
	}
	pthread_mutex_destroy(&share->all_ready);
	pthread_mutex_destroy(&share->m_print);
	pthread_mutex_destroy(&share->m_over);
	ft_free_philo(share->philo);
}

int	ft_simulate(t_share *share)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&share->all_ready);
	while (i < share->info.num_philo)
	{
		if (pthread_create(&share->philo[i].tid, NULL, \
		ft_philo_routine, (void *) &share->philo[i]))
			return (ft_end_with_free(share->philo, "error: pthread_create"));
		i++;
	}
	share->start_time = ft_get_time_in_ms();
	pthread_mutex_unlock(&share->all_ready);
	ft_monitoring(share);
	ft_wait_all(share->philo);
	ft_stop_simulating(share);
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_share	share;

	if ((ac == 5) || (ac == 6))
	{
		if (ft_init_share(&share, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_simulate(&share) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_print_error("Invalid Number of Args");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
