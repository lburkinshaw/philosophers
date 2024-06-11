/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:16:09 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/11 11:59:40 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);//if change order in main, may need to free philos
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		printf("Fork %d mutex initiated at loc %p\n", i, (void *)&data->forks[i]);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	printf("Write_lock mutex initiated at loc %p\n", (void *)&data->write_lock);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	printf("Death_lock mutex initiated at loc %p\n", (void *)&data->death_lock);
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
		data->num_of_meals = ft_atoi(argv[5]); //Not sure this is the right place or data??
	else
		data->num_of_meals = -1;//or 0?
	data->start_time = get_current_time();
	data->dead_flag = false; //do i use this?
	data->can_write = true;
	if (init_mutexes(data) != 0)
	{
		destroy_data_mutexes(data);
		if (data->forks)
			free(data->forks);//NOT SURE ABOUT THIS. is this enough?? do i need a loop?
		printf("Error data inititalizing mutexes\n");
		return (1);
		//anything to free yet?? Forks??
	}
	print_data(data); //delete
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
		philo[i].last_meal_time = get_current_time();
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
		if (pthread_mutex_init(&philo[i].alive_lock, NULL) != 0)
		{
			destroy_data_mutexes(data);
			printf("Error initializing meal_lock mutex\n");
			return (1);
		}
		printf("Meal_lock mutex initialized at loc %p\n", (void *)&philo[i].meal_lock);
		i++;
	}
	print_philos(philo, *data);
	return (0);
}
