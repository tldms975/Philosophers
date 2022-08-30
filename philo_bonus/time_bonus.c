/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:48:22 by sielee            #+#    #+#             */
/*   Updated: 2022/08/30 16:01:31 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_get_time_in_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (((long long)(time.tv_sec * 1e3) \
	+ (long long)(time.tv_usec / 1e3)));
}

long long	ft_get_time_stamp(long long start_time)
{
	long long	end_time;

	end_time = ft_get_time_in_ms();
	return (end_time - start_time);
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = ft_get_time_in_ms();
	while (time >= (ft_get_time_in_ms() - start_time))
	{
		usleep(500);
	}
}
