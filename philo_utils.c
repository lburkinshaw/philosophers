/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:15:37 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/30 14:33:43 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//ADD FUNCTION  TO SET STRUCTS TO ZERO.

void	destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	(void)philo;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			//free stuff - forks, philos.
			error_n_exit("Error destroying mutexes\n");
		}
		i++;
	}
	/*DESTROY OTHER MUTEXES
	if (pthread_mutex_destroy())
	*/
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
