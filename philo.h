/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:40 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/07 15:44:48 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <unistd.h> //usleep, write
# include <sys/time.h> //gettimeofday
# include <pthread.h> // threads: pthread_create, pthread_join, pthread_detach
					  // mutexes: pthread_mutex_init, destroy, lock, unlock
# include <stdbool.h>
# define FT_LONG_MAX 9223372036854775807L //for atoi

typedef struct timeval	t_timeval;//why here?

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	size_t			start_time;
	bool			dead_flag;
	pthread_mutex_t	*forks;//array of forks, can be accessed by all philos.
	pthread_mutex_t	write_lock;//does this need to be a pointer??
	pthread_mutex_t	death_lock;
}	t_data;
//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


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
	// pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	// pthread_mutex_t	death;
	// pthread_mutex_t	meals_flag;
	// t_mutex	mutex;
}	t_philo;

//	ADD FUNCTIONS
int		main(int argc, char **argv);
void	error_msg(char *msg);//delete?
void	error_n_exit(char *msg);///delete
size_t	get_current_time(void);
int		init_data(char **argv, t_data *data);
int		init_mutexes(t_data *data);
// void	init_forks(t_data *data);
int		init_philos(t_philo *philo, t_data *data);
int		init_threads(t_philo *philo, t_data *data);
void	*monitoring(void *ptr);
void	*philosophize(void *ptr);
void	set_dead_flag(t_philo *philo);
// int		death_check(t_philo *philo);
void	get_forks(t_philo *philo, pthread_mutex_t **f1, pthread_mutex_t **f2);
void	print_action(t_philo *philo, char *action);
void	ft_usleep(size_t milisecs);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif