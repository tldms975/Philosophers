/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:14:45 by sielee            #+#    #+#             */
/*   Updated: 2022/08/22 17:17:42 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

//#include "philo.h"

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
	c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long		res;
	int						sign;

	res = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res = res + *str - '0';
		str++;
	}
	return (res * sign);
}
