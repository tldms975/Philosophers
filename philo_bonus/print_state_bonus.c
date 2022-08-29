/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:28:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/29 13:12:27 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_done(t_philo *philo)
{
	sem_wait(philo->share->sm_print);
	printf(COL_GREEN "Simulation stopped successfully!\n" COL_ORIGIN);
}

void	ft_print_die(t_philo *philo)
{
	sem_wait(philo->share->sm_print);
	printf(COL_RED "%lld ms\t%d died\n" COL_ORIGIN, \
	ft_get_time_stamp(philo->share->start_time), philo->id);
}

void	ft_print_state(t_philo *philo, t_state state)
{
	sem_wait(philo->share->sm_print);
	printf("%lld ms\t%d ", ft_get_time_stamp(philo->share->start_time), \
	philo->id);
	if (state == FORK)
		printf("has taken a fork\n");
	else if (state == EAT)
		printf("is eating\n");
	else if (state == SLEEP)
		printf("is sleeping\n");
	else if (state == THINK)
		printf("is thinking\n");
	sem_post(philo->share->sm_print);
}
