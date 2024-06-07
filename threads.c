/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:36:49 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/07 13:58:22 by lburkins         ###   ########.fr       */
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

static int	join_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			//free philos and forks
			printf("Error joining philo threads\n");
			return (-1);
		}
		i++;
	}
	return (0);
}



int	init_threads(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
	{
		//free stuff - forks, philos. destroy mutexes.
		printf("Error creating monitoring thread\n");
		return (-1);
	}
	// ft_usleep(10); //to allow time for the monitoring thread to start. This might be better in a while loop that waits for monitoring to set "monitor_ready"
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philosophize, &philo[i]) != 0)
		{
			//free stuff - forks, philos. detach monitoring thread. destroy mutexes.
			printf("Error creating philo threads\n");
			return (-1);
		}
		printf("Created thread for philo %d\n", i);
		i++;
	}
	//if (mointoring(philo) == 1)
		//detach_threads, error and exit.
	//else
	// {
		// }
	if (pthread_join(monitor, NULL) != 0)
		{
			//free stuff - forks, philos. threads and mutexes. (or do in function)
			printf("Error joining monitoring thread\n");
			return (-1);
		}
	if (join_threads(philo, data) != 0)
	{
		//free stuff - forks, philos. threads and mutexes. (or do in function)
		return (-1);
	}
	// destroy_mutexes(philo, data);
	return (0);
}
