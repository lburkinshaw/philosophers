/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:32:11 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/30 16:04:35 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	eating(t_philo *philo)
// {
	
// }
// static void	thinking(t_philo *philo)
// {
	
// }
// static void	sleeping(t_philo *philo)
// {
	
// }

void	*philosophize(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->alive == true && philo->all_meals_eaten == false)
	{
		printf("test\n");//infinite loop until add in meal count and deaths.
		sleep(5);//just to delay printf statement to check prev info.
		// eating(philo);
		// sleeping(philo);
		// thinking(philo);
	}
	return (NULL);
}
