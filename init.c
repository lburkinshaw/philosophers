/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:16:09 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/13 11:13:50 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->full_lock, NULL) != 0)
		return (1);
	return (0);
}
void	print_data(t_data *data)
{
	printf("Num of philos: %d\n", data->num_of_philos);
	printf("Time to die: %zu\n", data->time_to_die);
	printf("Time to eat: %d\n", data->time_to_eat);
	printf("Time to sleep: %d\n", data->time_to_sleep);
}

int	init_data(char **argv, t_data *data)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead_flag = false;
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
	data->start_time = get_current_time();
	data->dead_flag = false;
	data->can_write = true;
	data->full_flag = false;
	if (init_mutexes(data) != 0)
	{
		destroy_data_mutexes(data);
		printf("Error inititalizing data mutexes\n");
		return (1);
	}
	return (0);
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

int	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].data = data;
		philo[i].philo_index = i + 1;
		philo[i].num_meals_eaten = 0;
		philo[i].last_meal_time = data->start_time;//was previously getcurrenttime but this seems more consistent
		philo[i].alive = true;
		philo[i].all_meals_eaten = false;
		philo[i].right_fork = &data->forks[i];
		if (i == (data->num_of_philos - 1))
			philo[i].left_fork = &data->forks[0];
		else
			philo[i].left_fork = &data->forks[i + 1];
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
		{
			destroy_data_mutexes(data);
			printf("Error initializing meal_lock mutex\n");
			return (1);
		}
		// if (pthread_mutex_init(&philo[i].alive_lock, NULL) != 0)
		// {
		// 	destroy_data_mutexes(data);
		// 	printf("Error initializing meal_lock mutex\n");
		// 	return (1);
		// }
		i++;
	}
	print_philos(philo, *data);//delete later
	return (0);
}
