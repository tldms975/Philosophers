/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:16:41 by sielee            #+#    #+#             */
/*   Updated: 2022/08/27 17:16:44 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, &"\n", 1);
}

int	ft_print_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_end_with_free(t_philo *philo, char *err_msg)
{
	ft_print_error(err_msg);
	ft_free_philo(philo);
	return (EXIT_FAILURE);
}
