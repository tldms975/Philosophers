/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:51:24 by sielee            #+#    #+#             */
/*   Updated: 2022/08/22 22:58:20 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, &"\n", 1);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
}

int	ft_end_with_free(t_philo *philo, char *err_msg)
{
	ft_error(err_msg);
	ft_free_philo(philo);
	return (EXIT_FAILURE);
}
