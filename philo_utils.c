/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:15:37 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/11 12:44:01 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//ADD FUNCTION  TO SET STRUCTS TO ZERO??





// void	get_forks(t_philo *philo, pthread_mutex_t **f1, pthread_mutex_t **f2)
// {
// 	if (philo->philo_index % 2 == 0)//alternated order odd/even philos pick up forks (left or right first)
// 	{
// 		*f1 = philo->left_fork;
// 		*f2 = philo->right_fork;
// 	}
// 	else
// 	{
// 		*f1 = philo->right_fork;
// 		*f2 = philo->left_fork;
// 	}
// }

void	ft_usleep(size_t milisecs)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < milisecs)
		usleep(500);
}

void	print_death(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%d %d has died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_action(t_philo *philo, char *action)
{
	int	timestamp;
	if (anyone_dead_yet(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = get_current_time() - philo->data->start_time;
	if (philo->data->can_write == false || anyone_dead_yet(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
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
