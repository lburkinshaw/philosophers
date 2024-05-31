/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:36:49 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/31 13:18:24 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
//commented out until write in monitoring function.
static void	detach_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_detach(philo[i].thread) != 0)
		{
			//free philos and forks
			error_n_exit("Error joining threads\n");
		}
		i++;
	}
}*/

static void	join_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			//free philos and forks
			error_n_exit("Error joining threads\n");
		}
		i++;
	}
}

void	init_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philosophize, &philo[i]) != 0)
		{
			//free stuff - forks, philos.
			error_n_exit("Error creating philo threads\n");
		}
		printf("Created thread for philo %d\n", i);
		usleep(42); //need to check why?
		i++;
	}
	//if (mointoring(philo) == 1)
		//detach_threads, error and exit.
	//else
	// {
	// 	if (join_threads(philo) != 0)
	// 	{
	// 		//free stuff - forks, philos.
	// 		error_n_exit("Error joining philo threads\n");
	// 	}
	// }	
	join_threads(philo, data);
	// destroy_mutexes(philo, data);
}
