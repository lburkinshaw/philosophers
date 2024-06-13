/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:15:37 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/13 13:17:30 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//ADD FUNCTION  TO SET STRUCTS TO ZERO??
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
		// printf("noticed dead philo and exiting\n");
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

int	all_full_yet(t_data *data)
{
	pthread_mutex_lock(&data->full_lock);
	if (data->full_flag == true)
	{
		printf("all full\n");
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

void	ft_usleep(size_t milisecs)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milisecs)
	{
		usleep(500);
	}
}

void	print_death(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%d %d died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_action(t_philo *philo, char *action)
{
	int	timestamp;
	if (anyone_dead_yet(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	if (philo->data->can_write == true || anyone_dead_yet(philo->data) == 0)
		printf("%d %d %s\n", timestamp, philo->philo_index, action);
	pthread_mutex_unlock(&philo->data->write_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("Error: gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	ft_check_ovrflo(int neg)
{
	if (neg == 1)
		return ((int) FT_LONG_MAX);
	return ((int)-FT_LONG_MAX - 1L);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		isneg;
	long	nb;
	long	pre;

	i = 0;
	nb = 0;
	isneg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		pre = nb;
		nb = (nb * 10) + (str[i] - '0');
		if (nb < 0 || pre > nb)
			return (ft_check_ovrflo(isneg));
		i++;
	}
	return (nb * isneg);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
