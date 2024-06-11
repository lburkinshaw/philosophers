/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:49:55 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/11 14:09:21 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_value(char *arg)
{
	int	i;

	i = 0;
	if (ft_atoi(arg) < 0)
	{
		printf("Error. Arguments cannot be negative\n");
		return (1);
	}
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("Error. Arguments must be positive numbers\n"); //i think
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	printf("checking args\n");
	if (argc < 5 || argc > 6)
	{
		printf("Error: Incorrect number of arguments\n"); //5/6: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
		return (-1);
	}
	if (ft_atoi(argv[1]) < 1)//checks number_of_philos
	{
		printf("Error. At least 1 philosopher required\n");
		return (-1);
	}
	while (argv[i])
	{
		if (check_value(argv[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_data			data;

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_data(argv, &data) != 0)
	{
		destroy_data_mutexes(&data);//inc. data->forks
		return (1);
	}
	philo = malloc(sizeof(t_philo) * data.num_of_philos);
	if (!philo)
	{
		destroy_data_mutexes(&data);
		printf("Malloc error: creating philos\n");
		return (1);
	}
	if (init_philos(philo, &data) != 0)
	{
		destroy_data_mutexes(&data);
		return (1);
	}
	if (init_threads(philo, &data)!= 0)
	{
		destroy_mutexes(&data, philo);//free stuff?
		return (1);
	}
	// free_philos(&philo);//only malloced once so only ned to free once?
	free(philo);
	printf("The End\n");
	return (0);
}
