/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:16:09 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/31 10:50:57 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		error_n_exit("Malloc error: creating forks\n");//if change order in main, may need to free philos
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		printf("Fork %d mutex initiated at loc %p\n", i, (void *)&data->forks[i]);
		i++;
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	printf("Meal_lock mutex initiated at loc %p\n", (void *)&data->meal_lock);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	printf("Write_lock mutex initiated at loc %p\n", (void *)&data->write_lock);
		return (0);
}

// int	init_mutexes(t_data data, t_philo *philo)
// {
// 	// if (init_forks(data) != 0)
// 	// 	return (1); //return 1 is more efficient b/c need to destroy all mutexes
// 	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
// 		return (1);
// 	printf("test\n");
// 	if (pthread_mutex_init(&data.write_lock, NULL) != 0)
// 			return (1);
// 	// if (pthread_mutex_init(&philo->mutex.death_lock, NULL) != 0)
// 	// 	return (1);
// 	return (0);
// }


void	init_data(char **argv, t_data *data)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]); //Not sure this is the right place or data??
	else
		data->num_of_meals = -1;//or 0?
	data->start_time = get_current_time();
	if (init_mutexes(data) != 0)
	{
		//anything to free yet?? or destroy??
	}
}

void	print_philos(t_philo *philo, t_data data)
{
	int	i = 0;
	while (i < data.num_of_philos)
	{
		printf("PRINTING PHILO NUM: %d\n", philo[i].philo_index);
		printf("index: %d\n", philo[i].philo_index);
		printf("right fork: %p\n", (void *)philo[i].right_fork);
		printf("left fork: %p\n", (void *)philo[i].left_fork);
		printf("philo alive: %d\n", philo[i].alive);
		printf("data test, start time: %zu\n", philo[i].data->start_time);
		printf("philo alive: %d\n", philo[i].alive);
		printf("philo meals eaten: %d\n", philo[i].num_meals_eaten);
		printf("philo last meal: %zu\n", philo[i].last_meal_time);
		i++;
	}
}

void	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].philo_index = i + 1;
		philo[i].data = data;
		philo[i].num_meals_eaten = 0;
		philo[i].last_meal_time = 0;
		philo[i].alive = true;
		philo[i].all_meals_eaten = false;
		philo[i].right_fork = &data->forks[i];
		if (i == (data->num_of_philos - 1))
			philo[i].left_fork = &data->forks[0];
		else
			philo[i].left_fork = &data->forks[i + 1];
		i++;
	}
	print_philos(philo, *data);
	init_threads(philo, data);
	//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
}
