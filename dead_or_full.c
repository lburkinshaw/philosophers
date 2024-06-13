/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_or_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:38:52 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/13 16:48:18 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->all_meals_eaten == true)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	anyone_dead_yet(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->dead_flag == true)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

static int	all_full_yet(t_data *data)
{
	pthread_mutex_lock(&data->full_lock);
	if (data->full_flag == true)
	{
		pthread_mutex_unlock(&data->full_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->full_lock);
	return (0);
}

int	dead_or_full(t_data *data)
{
	if (anyone_dead_yet(data) || all_full_yet(data))
		return (1);
	else
		return (0);
}
