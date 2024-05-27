/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:16:09 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/27 15:04:25 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(pthread_mutex_t *forks, int n, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < n)//creates all forks within pthread_mutex_t struct using thread_mutex_init (already in pthread library)
	{
	if (pthread_mutex_init(&forks[i], NULL) != 0)
		return (1);
	i++;
	}
	i = 0;
	printf("FORKS\n");
	while (i < n)//assign left and right fork to each philo.
	{
		philo[i].left_fork = &forks[i];
		if (i == 0)
			philo[i].right_fork = &forks[n - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}

	return (0);
}

int	init_mutexes(pthread_mutex_t *forks, t_philo *philo, int num_of_philos)
{
	if (init_forks(forks, num_of_philos, philo) != 0)
		return (1); //return 1 is more efficient b/c need to destroy all mutexes
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		return (1);
	printf("test\n");
	if (pthread_mutex_init(&philo->write_lock, NULL) != 0)
			return (1);
	// if (pthread_mutex_init(&philo->mutex.death_lock, NULL) != 0)
	// 	return (1);
	return (0);
}

void	print_philos(t_philo *philo, t_data data)
{
	int	i = 0;
	while (i < data.num_of_philos)
	{
		printf("PRINTING PHILO NUM: %d\n", philo[i].philo_index);
		printf("data test, start time: %zu\n", philo[i].data->start_time);
		printf("philo alive: %d\n", philo[i].alive);
		printf("philo alive: %d\n", philo[i].alive);
		printf("philo meals eaten: %d\n", philo[i].num_meals_eaten);
		printf("philo last meal: %zu\n", philo[i].last_meal_time);
		i++;
	}
}

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	printf("init data\n");
	data.num_of_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.num_of_meals =  ft_atoi(argv[5]); //Not sure this is the right place or data??
	else
		data.num_of_meals = -1;
	data.start_time = get_current_time();
	return (data);
}

//below also doesnt seem right... review logic
void	init_philos(t_philo *philo, t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_of_philos)
	{
		philo[i].philo_index = i + 1;
		// printf("PHILO - index: %d\n", philo[i].philo_index);
		philo[i].data = &data;
		// printf("data test, argv[2]: %d\n", philo[i].data.time_to_die);
		philo[i].alive = 1;
		// printf("philo alive: %d\n", philo[i].alive);
		philo[i].num_meals_eaten = 0;
		// printf("philo meals eaten: %d\n", philo[i].num_meals_eaten);
		philo[i].last_meal_time = 0;
		i++;
		// print_p_struct(philo, i);
	}
	print_philos(philo, data);
	//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
}
