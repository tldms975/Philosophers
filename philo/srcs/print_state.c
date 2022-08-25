/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:28:19 by sielee            #+#    #+#             */
/*   Updated: 2022/08/25 16:03:43 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_state(t_philo *philo, t_state state)
{
	t_timeval	timeval;

	gettimeofday(&timeval, NULL);//
	printf("%u %d", (timeval.tv_usec / 1000), philo->id);
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
