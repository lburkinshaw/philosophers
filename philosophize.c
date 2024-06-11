/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:32:11 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/11 12:39:47 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int anyone_dead_yet(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
		if (data->dead_flag == true)
		{
			// printf("noticed dead philo and exiting\n");
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_lock);
		return (0);
}
void	get_forks(t_philo *philo, pthread_mutex_t **f1, pthread_mutex_t **f2)
{
	if (philo->philo_index % 2 == 0)//alternated order odd/even philos pick up forks (left or right first)
	{
		*f1 = philo->left_fork;
		*f2 = philo->right_fork;
	}
	else
	{
		*f1 = philo->right_fork;
		*f2 = philo->left_fork;
	}
}

static int	eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = NULL;
	second_fork = NULL;
	get_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork");//need to check if have to specify left/right fork??
	//add in condition for if only 1 philo?? see Tom's code.
	if (philo->data->num_of_philos == 1)
	{
		// printf("test philos = 1");
		ft_usleep(philo->data->time_to_die);
		//do something else???
	}
	if (anyone_dead_yet(philo->data))
    {
        pthread_mutex_unlock(first_fork);
        return (1);
    }
	pthread_mutex_lock(second_fork);
	if (anyone_dead_yet(philo->data))
    {
        pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
        return (1);
    }
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);//to avoid race condition when monitoring checks this.
	philo->last_meal_time = get_current_time();
	philo->num_meals_eaten++;
	// printf("Philo %d num of meals eaten: %d\n", philo->philo_index, philo->num_meals_eaten);
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (anyone_dead_yet(philo->data) == 1)
		return (1);
	print_action(philo, "is thinking");
	return (anyone_dead_yet(philo->data));
}
static int	sleeping(t_philo *philo)
{
	// set_all_meals_eaten_flag(philo);
	if (anyone_dead_yet(philo->data) == 1)
		return (1);
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	return (anyone_dead_yet(philo->data));
}


void	*philosophize(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->alive == true && philo->all_meals_eaten == false
		/*&& philo->data->dead_flag == false*/)
	{
		// printf("test\n");//infinite loop until add in meal count and deaths.
		// sleep(5);//just to delay printf statement to check prev info.
		// pthread_mutex_lock(&philo->data->death_lock);

		if (anyone_dead_yet(philo->data) == 1)
		{
			printf("%d noticed dead philo and exiting\n", philo->philo_index);
			return (ptr);
		}
		if (eating(philo) == 1)
		{
			printf("%d noticed dead philo and exiting\n", philo->philo_index);
			return (ptr);
		}
		// if (anyone_dead_yet(philo->data) == 1)
		// {
		// 	printf("%d noticed dead philo and exiting\n", philo->philo_index);
		// 	return (ptr);
		// }
		if (sleeping(philo) == 1)
		{
			printf("%d noticed dead philo and exiting\n", philo->philo_index);
			return (ptr);
		}
		// if (anyone_dead_yet(philo->data) == 1)
		// {
		// 	printf("%d noticed dead philo and exiting\n", philo->philo_index);
		// 	return (ptr);
		// }
		if (thinking(philo) == 1)
		{
			printf("%d noticed dead philo and exiting\n", philo->philo_index);
			return (ptr);
		}
	}
		return (NULL);
}
