/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:52:07 by sielee            #+#    #+#             */
/*   Updated: 2022/08/23 03:34:15 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_philo *philo, t_info *info, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		philo[i].id = i;
		philo[i].info = info;
		i++;
	}
}

void	ft_init_info(t_info *info, char *av[])
{
	info->num_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	if (av[5])
		info->num_must_eat = ft_atoi(av[5]);
	else
		info->num_must_eat = 0;
}

int	ft_init_play(t_play *play, t_info *info, char *av[])
{
	t_philo	*philo;

	ft_init_info(info, av);
	philo = ft_malloc(sizeof(t_info) * (info->num_philo));
	if (!philo)
		return (EXIT_FAILURE);
	ft_init_philo(philo, info, info->num_philo);
	play->info = info;
	play->philo = philo;
}

void	ft_print_state(t_philo *philo, t_state *state)
{
	t_timeval	timeval;

	gettimeofday(&timeval, NULL);//
	printf("%u %d", timeval.tv_usec, philo->id);
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

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	ft_print_state(philo, EAT);
	philo->meal_cnt += 1;
	usleep(philo->info->time_eat);//
	pthread_mutex_unlock(philo->mutex);
}

void	ft_wait_others()
{
	
}

void	ft_think(t_philo *philo)
{

}

void	ft_sleep(t_philo *philo)
{
	
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_wait_others(philo);
	ft_eat(philo);
	ft_think(philo);
	ft_sleep(philo);
}

int	ft_run_philo(t_play *play)
{
	int	i;

	i = 0;
	while (i < play->info->num_philo)
	{
		if (pthread_create(&play->philo[i].tid, NULL, \
		ft_philo_routine, (void *) &play->philo[i]))
			return (ft_end_with_free(play->philo, "error: pthread_create"));
		i++;
	}
		
}

int	main(int ac, char *av[])
{
	t_play	play;
	t_info	info;

	if ((ac == 5) || (ac == 6))
	{
		if (ft_init_play(&play, &info, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_run_philo(&play) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_error("Invalid Number of Args");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
