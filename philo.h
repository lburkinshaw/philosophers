/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:40 by lburkins          #+#    #+#             */
/*   Updated: 2024/05/27 15:29:37 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //mallloc, free
# include <string.h> //memset
# include <unistd.h> //usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> // threads: pthread_create, pthread_detach, pthread_join, pthread_mutex_init
# define FT_LONG_MAX 9223372036854775807L //for atoi

typedef struct timeval	t_timeval;//why here?

typedef struct s_data
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	size_t	start_time;
}	t_data;

// typedef struct s_mutex
// {
// 	pthread_mutex_t	*right_fork;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t	*meal_lock;
// }	t_mutex;

typedef struct s_philo
{
	t_data			*data; //could this be a pointer??
	int				philo_index;
	int				alive; //bool?
	int				num_meals_eaten;
	size_t			last_meal_time;
	pthread_mutex_t	*right_fork;//points to fork in pthread_mutex_t struct "forks"
	pthread_mutex_t	*left_fork;
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
t_data	init_data(int argc, char **argv);
int		init_mutexes(pthread_mutex_t *forks, t_philo *philos, int num_of_philos);
int		init_forks(pthread_mutex_t *forks, int n, t_philo *philo);
void	init_philos(t_philo *philo, t_data data);

#endif