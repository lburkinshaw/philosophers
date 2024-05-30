/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:49:55 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/30 13:17:02 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_value(char *arg)
{
	int	i;

	i = 0;
	if (ft_atoi(arg) < 0)
		error_n_exit("Error. Arguments cannot be negative\n");
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			error_n_exit("Error. Arguments must be positive numbers\n"); //i think
		i++;
	}
}

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	printf("checking args\n");
	if (argc < 5 || argc > 6)
		error_n_exit("Error: Incorrect number of arguments\n"); //5/6: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	if (ft_atoi(argv[1]) < 1)//checks number_of_philos
		error_n_exit("Error. At least 1 philosopher required\n");
	while (argv[i])
	{
		check_value(argv[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_data			data;

	check_args(argc, argv);
	init_data(argv, &data);//inc. data->forks
	philo = malloc(sizeof(t_philo) * data.num_of_philos);
	if (!philo)
		error_n_exit("Malloc error: creating philos\n");
		
	//init_mutexes function here
	init_philos(philo, &data);
	/*if (init_mutexes(data, philo) != 0)
	{
		//destroy mutexes
		error_n_exit("Error initializing mutexes\n");
	}*/
	// init_threads(philos, forks);
	return (0);
}
