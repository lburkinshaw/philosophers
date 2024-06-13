/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:50:21 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/12 14:15:30 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		// pthread_mutex_destroy(&philo[i].alive_lock);//may not be necessary
		i++;
	}
	printf("destroyed philo mutexes\n");
}

void	destroy_data_mutexes(t_data *data)
{
	int		i;
	t_data	data_tmp;

	i = 0;
	data_tmp = *data;
	while (i < data_tmp.num_of_philos)
	{
		pthread_mutex_destroy(&data_tmp.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data_tmp.death_lock);
	pthread_mutex_destroy(&data_tmp.write_lock);
	pthread_mutex_destroy(&data_tmp.full_lock);
	free(data->forks);
	data->forks = NULL;
	printf("destroyed data mutexes\n");
}

void	cleanup(t_data *data, t_philo *philo)
{
	destroy_data_mutexes(data);
	destroy_philo_mutexes(philo);
	free(philo);
	printf("Cleanup complete\n");
}
