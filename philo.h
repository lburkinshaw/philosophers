/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:40 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/31 13:58:39 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> // threads: pthread_create, pthread_detach, pthread_join, pthread_mutex_init
#include <stdbool.h>
# define FT_LONG_MAX 9223372036854775807L //for atoi

typedef struct timeval	t_timeval;//why here?

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	pthread_mutex_t	*forks;//array of forks, can be accessed by all philos.
	pthread_mutex_t	write_lock;//does this need to be a pointer??
	pthread_mutex_t	meal_lock;
	size_t			start_time;
}	t_data;

// typedef struct s_mutex
// {
// 	pthread_mutex_t	*right_fork;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t	*meal_lock;
// }	t_mutex;


//ADD MONITORING STRUCT FOR DEATH AND EVERYBODY FULL?

typedef struct s_philo
{
	t_data			*data; //could this be a pointer??
	int				philo_index;
	int				num_meals_eaten;
	size_t			last_meal_time;
	bool			alive;
	bool			all_meals_eaten;
	pthread_mutex_t	*right_fork;//points to fork in pthread_mutex_t struct "forks" == philo ID
	pthread_mutex_t	*left_fork; //== philo ID +1 (or fork 0 in case of last philo in array.) 
	pthread_t		thread;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	// pthread_mutex_t	death;
	// pthread_mutex_t	meals_flag;
	// t_mutex	mutex;
}	t_philo;

//	ADD FUNCTIONS
int		main(int argc, char **argv);
void	error_msg(char *msg);
void	error_n_exit(char *msg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	get_current_time(void);
void	init_data(char **argv, t_data *data);
int		init_mutexes(t_data *data);
// void	init_forks(t_data *data);
void	init_philos(t_philo *philo, t_data *data);
void	init_threads(t_philo *philo, t_data *data);
void	*philosophize(void *ptr);
void	print_action(t_philo *philo, char *action);

#endif