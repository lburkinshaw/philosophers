/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:30:08 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/07 14:24:27 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	philo->data->dead_flag = true;
	pthread_mutex_unlock(&philo->data->death_lock);
}

static int	philo_dead(t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_current_time();
	if ((current_time - philo->last_meal_time) >= philo->data->time_to_die)
	{
		print_action(philo, "died");
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	death_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philos && philo->data->dead_flag == false)
	{
		if (philo_dead(&philo[i]))
		{
			set_dead_flag(philo);
			philo[i].alive = false;
			printf("DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	meal_check(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->num_of_meals == -1)
		return (0);
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].num_meals_eaten < philo->data->num_of_meals)
		{
			pthread_mutex_unlock(&philo[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	philo[i].all_meals_eaten = true;//Finn marks dead_flag??
	//should i print a message here?
	return (1);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	printf("test monitoring\n");
	philo = (t_philo *)ptr;
	while (1)
	{
		if (meal_check(philo) || death_check(philo))
			break ;
	}
	return (NULL);//or NULL like in philosphize?
}
