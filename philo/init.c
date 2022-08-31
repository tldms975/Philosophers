/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:37:57 by sielee            #+#    #+#             */
/*   Updated: 2022/08/31 22:45:44 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_set_fork_direction(t_philo *philo, int i, int all)
{
	philo[i].r_fork = &philo[i].fork;
	philo[i].stat_r_fork = &philo[i].stat_fork;
	if (i == 0)
	{
		philo[i].l_fork = &philo[all - 1].fork;
		philo[i].stat_l_fork = &philo[all - 1].stat_fork;
	}
	else
	{
		philo[i].stat_l_fork = &philo[i - 1].stat_fork;
		philo[i].l_fork = &philo[i - 1].fork;
	}
}

static void	ft_init_philo(t_philo *philo, t_share *share)
{
	int	i;
	int	all;

	i = 0;
	all = share->info.num_philo;
	while (i < all)
	{
		philo[i].id = i + 1;
		philo[i].share = share;
		philo[i].meal_cnt = 0;
		philo[i].stat_fork = OFF;
		pthread_mutex_init(&philo[i].m_eat, NULL);
		pthread_mutex_init(&philo[i].fork, NULL);
		ft_set_fork_direction(philo, i, all);
		i++;
	}
}

static int	ft_init_info(t_info *info, char *av[])
{
	if (!ft_if_valid_args_range(av))
		return (ft_print_error("Invalid Args"));
	info->num_philo = ft_atoui(av[1]);
	info->time_die = ft_atoui(av[2]);
	info->time_eat = ft_atoui(av[3]);
	info->time_sleep = ft_atoui(av[4]);
	if (av[5])
		info->num_must_eat = ft_atoui(av[5]);
	else
		info->num_must_eat = 0;
	return (EXIT_SUCCESS);
}

int	ft_init_share(t_share *share, char *av[])
{
	t_philo	*philo;

	if (ft_init_info(&share->info, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo = ft_malloc(sizeof(t_philo) * (share->info.num_philo));
	if (!philo)
		return (EXIT_FAILURE);
	share->philo = philo;
	share->is_over = FALSE;
	share->is_ready = FALSE;
	pthread_mutex_init(&share->m_ready, NULL);
	pthread_mutex_init(&share->m_print, NULL);
	pthread_mutex_init(&share->m_over, NULL);
	ft_init_philo(philo, share);
	return (EXIT_SUCCESS);
}
