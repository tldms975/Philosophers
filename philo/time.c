/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:48:22 by sielee            #+#    #+#             */
/*   Updated: 2022/08/27 17:17:43 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
