/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lburkins <lburkins@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:40 by lburkins          #+#    #+#             */
/*   Updated: 2024/06/17 14:32:32 by lburkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <unistd.h> //usleep, write
# include <sys/time.h> //gettimeofday
# include <pthread.h> //Threads: create/join/detach. Mutexes: init/destroy/lock
# include <stdbool.h>
# define FT_LONG_MAX 9223372036854775807L //ft_atoi

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	size_t			start_time;
	bool			dead_flag;
	bool			full_flag;
	bool			can_write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	full_lock;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				philo_index;
	int				num_meals_eaten;
	size_t			last_meal_time;
	bool			all_meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	meal_lock;
}	t_philo;

int		main(int argc, char **argv);
int		init_data(char **argv, t_data *data);
int		init_philos(t_philo *philo, t_data *data);
int		init_threads(t_philo *philo, t_data *data);
void	*philosophize(void *ptr);
void	*monitoring(void *ptr);
int		anyone_dead_yet(t_data *data);
int		am_i_full(t_philo *philo);
int		dead_or_full(t_data *data);
void	print_action(t_philo *philo, char *action);
void	print_death(t_philo *philo);
int		destroy_data_mutexes(t_data *data);
void	cleanup(t_data *data, t_philo *philo);
size_t	get_current_time(void);
void	ft_usleep(size_t milisecs);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif