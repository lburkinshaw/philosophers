/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:32:59 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/13 16:48:00 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
