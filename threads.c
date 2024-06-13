/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:36:49 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/13 16:21:47 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(pthread_t	monitor, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(monitor, NULL) != 0)
	{
		printf("Error joining monitoring thread\n");
		return (1);
	}
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error joining philo threads\n");
			return (1);
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
		printf("Error creating monitoring thread\n");
		return (1);
	}
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philosophize, \
			&philo[i]) != 0)
		{
			printf("Error creating philo threads\n");
			return (1);
		}
		i++;
	}
	if (join_threads(monitor, philo, data) != 0)
		return (1);
	return (0);
}
