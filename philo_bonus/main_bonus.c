/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:52:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/28 21:12:55 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	t_share	share;

	if ((ac == 5) || (ac == 6))
	{
		if (ft_init_share(&share, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_simulate(&share) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_print_error("Invalid Number of Args");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
