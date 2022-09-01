/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:37:57 by sielee            #+#    #+#             */
/*   Updated: 2022/09/01 16:26:20 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		sem_unlink("sm_eat");
		philo[i].sm_eat = sem_open("sm_eat", O_CREAT, 0644, 1);
		i++;
	}
	if (philo->share->info.num_philo == 1)
		sem_post(philo[0].share->sm_set_eat);
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

static void	ft_init_sem_in_share(t_share *share)
{
	sem_unlink("sm_start");
	share->sm_start = sem_open("sm_start", O_CREAT, 0644, 1);
	sem_unlink("sm_print");
	share->sm_print = sem_open("sm_print", O_CREAT, 0644, 1);
	sem_unlink("sm_fork");
	share->sm_fork = sem_open("sm_fork", O_CREAT, 0644, \
	share->info.num_philo);
	sem_unlink("sm_set_eat");
	share->sm_set_eat = sem_open("sm_set_eat", O_CREAT, 0644, \
	share->info.num_philo / 2);
	sem_unlink("sm_dead");
	share->sm_dead = sem_open("sm_dead", O_CREAT, 0644, 0);
	sem_unlink("sm_done");
	share->sm_done = sem_open("sm_done", O_CREAT, 0644, 0);
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
	share->is_dead = FALSE;
	ft_init_sem_in_share(share);
	ft_init_philo(philo, share);
	return (EXIT_SUCCESS);
}
