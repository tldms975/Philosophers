/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:14:45 by sielee            #+#    #+#             */
/*   Updated: 2022/08/27 17:17:28 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
	c == ' ')
		return (TRUE);
	return (FALSE);
}

static t_bool	ft_check_unsigned_int_range(char *s)
{
	if ((s[0] <= '4' && s[0] >= '0') && (s[1] <= '2' && s[1] >= '0') \
	&& (s[2] <= '9' && s[2] >= '0') && (s[3] <= '4' && s[3] >= '0') \
	&& (s[4] <= '9' && s[4] >= '0') && (s[5] <= '6' && s[5] >= '0') \
	&& (s[6] <= '7' && s[6] >= '0') && (s[7] <= '2' && s[7] >= '0') \
	&& (s[8] <= '9' && s[8] >= '0') && (s[9] <= '5' && s[9] >= '0'))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	ft_check_num_range(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

t_bool	ft_if_valid_args_range(char *av[])
{
	int	i;
	int	len;

	i = 1;
	while (i < 6)
	{
		if (i == 5 && !av[i])
			return (TRUE);
		while (ft_is_space(*av[i]))
			av[i]++;
		if (*av[i] == '+')
			av[i]++;
		while (*av[i] == '0')
			av[i]++;
		if (!*av[i])
			return (FALSE);
		len = ft_strlen(av[i]);
		if (len > 9 || (len == 9 && !ft_check_unsigned_int_range(av[i])))
			return (FALSE);
		else if (!ft_check_num_range(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

unsigned int	ft_atoui(const char *str)
{
	unsigned int	res;

	res = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res = res + *str - '0';
		str++;
	}
	return (res);
}
