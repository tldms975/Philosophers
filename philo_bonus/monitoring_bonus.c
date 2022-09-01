/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:33:21 by sielee            #+#    #+#             */
/*   Updated: 2022/09/01 16:28:53 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_sign	ft_check_dead(t_philo *philo)
{
	t_info			*info;
	long long		starving;

	info = &philo->share->info;
	if (philo->meal_cnt == 0)
		starving = ft_get_time_stamp(philo->share->start_time);
	else
		starving = ft_get_time_stamp(philo->last_meal);
	if ((starving >= info->time_die) && !(philo->share->is_dead))
	{
		ft_print_die(philo);
		sem_post(philo->share->sm_dead);
		return (TRUE);
	}
	return (FALSE);
}

static void	*ft_over_if_dead(void *arg)
{
	t_philo	*a_philo;

	a_philo = (t_philo *)arg;
	while (TRUE)
	{
		sem_wait(a_philo->sm_eat);
		a_philo->share->is_dead = ft_check_dead(a_philo);
		sem_post(a_philo->sm_eat);
		usleep(500);
	}
	return (NULL);
}

void	ft_monitoring_in_each_philo(t_philo *a_philo)
{
	if (pthread_create(&a_philo->tid, NULL, \
	ft_over_if_dead, (void *) a_philo))
		ft_stop_by_error(a_philo->share, "pthread_create error");
}

static void	*ft_check_done(void *arg)
{
	unsigned int	i;
	t_share			*share;

	share = (t_share *)arg;
	i = 0;
	while (i < share->info.num_philo)
	{
		sem_wait(share->sm_done);
		i++;
	}
	if (!share->is_dead)
	{
		ft_print_done(share->philo);
		sem_post(share->sm_dead);
	}
	return (NULL);
}

void	ft_monitoring_in_parent(t_share *share)
{
	pthread_t		tid;
	unsigned int	i;

	i = 0;
	if (pthread_create(&tid, NULL, ft_check_done, (void *)share))
		ft_print_error("pthread_create error");
	sem_wait(share->sm_dead);
	ft_term_all_process(share->philo);
	share->is_dead = TRUE;
	while (i < share->info.num_philo)
	{
		sem_post(share->sm_done);
		i++;
	}
	pthread_join(tid, NULL);
}
