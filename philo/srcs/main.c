/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:52:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/24 20:37:03 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *philo, t_info *info)
{
	int	i;
	int	all;

	i = 0;
	all = info->num_philo;
	while (i < all)
	{
		philo[i].id = i;
		philo[i].info = info;
		pthread_mutex_init(&philo[i].mut_eat, NULL);
		philo[i].fork = OFF;
		philo[i].r_fork = philo[i].fork;
		if (i == 0)
			philo[i].l_fork = philo[all - 1].fork;
		else
			philo[i].l_fork = philo[i - 1].fork;
		i++;
	}
}

int	ft_init_info(t_info *info, char *av[])
{
	if (!ft_if_valid_args_range(av))
		return (ft_print_error("Invalid Args"));
	info->num_philo = ft_atoui(av[1]);
	info->time_die = ft_atoui(av[2]);
	info->time_eat = ft_atoui(av[3]);
	info->time_sleep = ft_atoui(av[4]);
	if (av[5])
		info->num_must_eat = ft_atoi(av[5]);
	else
		info->num_must_eat = 0;
	return (EXIT_SUCCESS);
}

int	ft_init_round(t_round *round, t_info *info, char *av[])
{
	t_philo	*philo;

	if (ft_init_info(info, av) == EXIT_FAILURE);
		return (EXIT_FAILURE);
	philo = ft_malloc(sizeof(t_info) * (info->num_philo));
	if (!philo)
		return (EXIT_FAILURE);
	ft_init_philo(philo, info);
	round->info = info;
	round->philo = philo;
	return (EXIT_SUCCESS);
}

void	ft_print_state(t_philo *philo, t_state *state)
{
	t_timeval	timeval;

	gettimeofday(&timeval, NULL);//
	printf("%u %d", timeval.tv_usec, philo->id);
	if (state == FORK)
		printf(" has taken a fork\n");
	else if (state == EAT)
		printf(" is eating\n");
	else if (state == SLEEP)
		printf(" is sleeping\n");
	else if (state == THINK)
		printf(" is thinking\n");
	else if (state == DIE)
		printf(" died\n");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_eat);
	ft_print_state(philo, FORK);
	*philo->l_fork = ON;
	*philo->r_fork = ON;
	ft_print_state(philo, EAT);
	philo->meal_cnt += 1;
	usleep(philo->info->time_eat);
	*philo->l_fork = OFF;
	*philo->r_fork = OFF;
	pthread_mutex_unlock(&philo->mut_eat);
}

void	ft_wait_others()
{
	
}

void	ft_think(t_philo *philo)
{
	ft_print_state(philo, THINK);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_state(philo, SLEEP);
	usleep(philo->info->time_sleep);
}

t_bool	ft_if_all_done(t_philo *philo)
{
	
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	while (1)
	{
		ft_wait_others(one_philo);
		ft_eat(one_philo);
		ft_think(one_philo);
		ft_sleep(one_philo);
		if (ft_if_all_done(one_philo) || (ft_if_someone_died() && !one_philo->info->num_must_eat))
			break ;
	}
}

int	ft_simulate(t_round *round)
{
	int	i;

	i = 0;
	while (i < round->info->num_philo)
	{
		if (pthread_create(&round->philo[i].tid, NULL, \
		ft_philo_routine, (void *) &round->philo[i]))
			return (ft_end_with_free(round->philo, "error: pthread_create"));
		i++;
	}
		
}

int	main(int ac, char *av[])
{
	t_round	round;
	t_info	info;

	if ((ac == 5) || (ac == 6))
	{
		if (ft_init_round(&round, &info, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_simulate(&round) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_print_error("Invalid Number of Args");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
