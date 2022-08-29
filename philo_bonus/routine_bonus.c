/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:45:11 by sielee            #+#    #+#             */
/*   Updated: 2022/08/29 16:14:18 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_eat(t_philo *a_philo)
{
	if (a_philo->share->info.num_philo == 1)
		sem_post(a_philo->share->sm_set_eat);
	sem_wait(a_philo->share->sm_set_eat);
	sem_wait(a_philo->share->sm_fork);
	ft_print_state(a_philo, FORK);
	sem_wait(a_philo->share->sm_fork);
	ft_print_state(a_philo, FORK);
	sem_wait(a_philo->sm_eat);
	ft_print_state(a_philo, EAT);
	a_philo->last_meal = ft_get_time_in_ms();
	usleep(a_philo->share->info.time_eat * 1e3);
	a_philo->meal_cnt += 1;
	if (a_philo->meal_cnt >= a_philo->share->info.num_must_eat)
	{
		a_philo->is_done = TRUE;
		sem_post(a_philo->share->sm_done);
	}
	sem_post(a_philo->sm_eat);
	sem_post(a_philo->share->sm_fork);
	sem_post(a_philo->share->sm_fork);
	sem_post(a_philo->share->sm_set_eat);
}

static void	ft_sleep_and_think(t_philo *a_philo)
{
	usleep(20);
	ft_print_state(a_philo, SLEEP);
	usleep(a_philo->share->info.time_sleep * 1e3);
	ft_print_state(a_philo, THINK);
	usleep(20);
}

void	ft_philo_routine(t_philo *a_philo)
{
	sem_wait(a_philo->share->sm_start);
	sem_post(a_philo->share->sm_start);
	ft_monitoring_in_each_philo(a_philo);
	while (TRUE)
	{
		ft_eat(a_philo);
		if (a_philo->is_done)
		{
			pthread_join(a_philo->tid, NULL);
			break ;
		}
		ft_sleep_and_think(a_philo);
	}
	if (a_philo->id == a_philo->share->info.num_philo)
		sem_post(a_philo->share->sm_over_after);
	return ;
}
