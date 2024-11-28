/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 19:34:24 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>   // for limits
# include <pthread.h>  // pthread functions
# include <stdbool.h>  // bool type
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

# define SUCCESS 0
# define ERROR 1
# define MAX_PHILOS 200
# define WARNING_ARGS "%sWarning: time below 60ms might cause timing issues%s\n"

// Colors for status messages
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

// Philosopher states
typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	FORK_TAKEN,
	DIED
}					t_state;

// Structure for each philosopher
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

// Structure for shared data
typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philosophers;
}					t_data;

// init.c
int					parse_args(t_data *data, int argc, char **argv);
int					init_philosophers(t_data *data);
int					init_mutex(t_data *data);
int					init_data(t_data *data, int argc, char **argv);

// check_args
int					is_valid_number(char *str);
int					check_limits(char *str);
int					check_philo_number(char *str);
void				check_min_values(char **argv);
int					check_args(int argc, char **argv);

// main.c

// monitor.c
bool				all_ate_enough(t_data *data);
bool				check_simulation_end(t_data *data);
bool				check_philosopher_death(t_data *data, int i);
void				*monitor_routine(void *philosopher_void);

// routines.c
int					take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
int					eat(t_philo *philo);
int					sleep_and_think(t_philo *philo);
void				*philosopher_routine(void *philosopher_void);

// status.c
bool				check_death(t_data *data);
void				print_status(t_philo *philo, t_state state);
void				clean_up(t_data *data);

// time.c
long long			time_diff(long long past, long long present);
void				precise_sleep(long long time);
long long			get_time(void);

// utils.c
int					ft_atoi(const char *str);
int					error_msg(char *str);
void				destroy_forks(t_data *data, int count);

#endif