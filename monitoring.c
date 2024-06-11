/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:30:08 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/11 14:20:34 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	set_dead_flag(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->death_lock);
// 	philo->data->dead_flag = true;
// 	pthread_mutex_unlock(&philo->data->death_lock);
// }

static int	philo_dead_yet(t_philo *philo)
{
	size_t	current_time;
	size_t	elapsed_time;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_current_time();
	elapsed_time = current_time - philo->last_meal_time;
	if (elapsed_time >= philo->data->time_to_die)
	{
		print_death(philo);
		printf("philo %d time since last meal: %zu\n", philo->philo_index, philo->last_meal_time);
		pthread_mutex_unlock(&philo->meal_lock);
		printf("DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD\n");
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
		// printf("death_check while loop\n");
		if (philo_dead_yet(&philo[i]))
		{
			printf("DEATH DETECTED\n");
			printf("philo has died, flag: %d\n", philo->data->dead_flag);
			// set_dead_flag(philo);
			pthread_mutex_lock(&philo->data->death_lock);
			philo->data->dead_flag = true;
			pthread_mutex_unlock(&philo->data->death_lock);
			philo[i].alive = false;//should this be inside death_lock mutex??
			printf("dead_flag set\n");
			printf("philo has died, flag: %d\n", philo->data->dead_flag);
			return (1);
		}
		i++;
	}
	// printf("test dead check end\n");
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
		// printf("meal_check while loop\n");
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].num_meals_eaten < philo->data->num_of_meals)
		{
			pthread_mutex_unlock(&philo[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	printf("philo %d, meals %d\n", (i + 1), philo[i].num_meals_eaten);
	printf("ALL MEALS EATEN\n");
	philo[i].all_meals_eaten = true;//Finn marks dead_flag??
	//should i print a message here?
	return (1);
}
void kill_philos(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].alive_lock);
		philo[i].alive = 0;
		pthread_mutex_unlock(&philo[i].alive_lock);
		i++;
	}
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;

	printf("test monitoring\n");
	philo = (t_philo *)ptr;
	while (1)
	{
		if (meal_check(philo) || death_check(philo))
		{
			printf("end loop \n");
			return (NULL) ;
		}
	}
	pthread_mutex_lock(&philo->data->write_lock);
	philo->data->can_write = false;
	kill_philos(philo);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (NULL);//or NULL like in philosphize?
}
