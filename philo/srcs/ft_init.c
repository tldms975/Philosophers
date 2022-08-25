/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:37:57 by sielee            #+#    #+#             */
/*   Updated: 2022/08/25 16:26:13 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_philo(t_round *round, t_philo *philo, t_info *info)
{
	int	i;
	int	all;

	i = 0;
	all = info->num_philo;
	while (i < all)
	{
		philo[i].id = i;
		philo[i].info = info;
		philo[i].share = &round->share;
		pthread_mutex_init(&philo[i].monitor, NULL);
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].r_fork = &philo[i].fork;
		if (i == 0)
			philo[i].l_fork = &philo[all - 1].fork;
		else
			philo[i].l_fork = &philo[i - 1].fork;
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

int	ft_init_round(t_round *round, t_info *info, char *av[])
{
	t_philo	*philo;

	if (ft_init_info(info, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo = ft_malloc(sizeof(t_info) * (info->num_philo));
	if (!philo)
		return (EXIT_FAILURE);
	round->info = info;
	round->philo = philo;
	pthread_mutex_init(&round->share, NULL);
	ft_init_philo(round, philo, info);
	return (EXIT_SUCCESS);
}
