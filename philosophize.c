/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:32:11 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/17 12:42:25 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dinner_for_one(t_philo *philo)
{
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

static int	eating(t_philo *philo)
{
	if (am_i_full(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->num_of_philos == 1)
		return (dinner_for_one(philo));
	pthread_mutex_lock(philo->left_fork);
	if (dead_or_full(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	print_action(philo, "is eating");
	philo->last_meal_time = get_current_time();
	philo->num_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (dead_or_full(philo->data) == 1)
		return (1);
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (dead_or_full(philo->data) == 1)
		return (1);
	print_action(philo, "is thinking");
	return (0);
}

void	*philosophize(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_index % 2 == 0)
		ft_usleep(42);
	while (!dead_or_full(philo->data))
	{
		if (eating(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
