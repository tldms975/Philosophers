/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:52:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/25 15:44:08 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_simulate(t_round *round)
{
	unsigned int	i;

	i = 0;
	while (i < round->info->num_philo)
	{
		if (pthread_create(&round->philo[i].tid, NULL, \
		ft_philo_routine, (void *) &round->philo[i]))
			return (ft_end_with_free(round->philo, "error: pthread_create"));
		pthread_join(round->philo[i].tid, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_round	round;
	t_info	info;

	if ((ac == 5) || (ac == 6))
	{
		if (ft_init_round(&round, &info, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_simulate(&round) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_print_error("Invalid Number of Args");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
