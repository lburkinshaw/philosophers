/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:32:11 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/31 14:36:21 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken right fork");;
	//add in condition for if only 1 philo?? see Tom's code.
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken left fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);//to avoid race condition when monitoring checks this.
	philo->last_meal_time = get_current_time();
	philo->num_meals_eaten++;
	// printf("Philo %d num of meals eaten: %d\n", philo->philo_index, philo->num_meals_eaten);
	pthread_mutex_unlock(&philo->meal_lock);
	usleep(philo->data->time_to_eat);//make own ft_usleep function?
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
static void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}
static void	sleeping(t_philo *philo)
{
	// set_all_meals_eaten_flag(philo);
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);//make own ft_usleep function?
	
}

void	*philosophize(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->alive == true && philo->all_meals_eaten == false)
	{
		// printf("test\n");//infinite loop until add in meal count and deaths.
		// sleep(5);//just to delay printf statement to check prev info.
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
