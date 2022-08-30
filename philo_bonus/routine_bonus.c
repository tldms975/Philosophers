/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:45:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 15:48:39 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_eat(t_philo *a_philo)
{
	sem_wait(a_philo->share->sm_set_eat);
	sem_wait(a_philo->share->sm_fork);
	ft_print_state(a_philo, FORK);
	sem_wait(a_philo->share->sm_fork);
	ft_print_state(a_philo, FORK);
	sem_wait(a_philo->sm_eat);
	ft_print_state(a_philo, EAT);
	a_philo->last_meal = ft_get_time_in_ms();
	ft_usleep(a_philo->share->info.time_eat);
	a_philo->meal_cnt += 1;
	if (a_philo->meal_cnt == a_philo->share->info.num_must_eat)
		sem_post(a_philo->share->sm_done);
	sem_post(a_philo->sm_eat);
	sem_post(a_philo->share->sm_fork);
	sem_post(a_philo->share->sm_fork);
	sem_post(a_philo->share->sm_set_eat);
}

static void	ft_sleep_and_think(t_philo *a_philo)
{
	ft_print_state(a_philo, SLEEP);
	ft_usleep(a_philo->share->info.time_sleep);
	ft_print_state(a_philo, THINK);
}

void	ft_philo_routine(t_philo *a_philo)
{
	sem_wait(a_philo->share->sm_start);
	sem_post(a_philo->share->sm_start);
	ft_monitoring_in_each_philo(a_philo);
	while (TRUE)
	{
		ft_eat(a_philo);
		ft_sleep_and_think(a_philo);
	}
	return ;
}
