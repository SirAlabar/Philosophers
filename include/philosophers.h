/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:22:40 by hluiz-ma          #+#    #+#           */
/*   Updated: 2024/01/09 19:22:40 by hluiz-ma         ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write, usleep
# include <pthread.h>    // pthread functions
# include <sys/time.h>   // gettimeofday
# include <stdbool.h>    // bool type
# include <limits.h>     // for limits

# define SUCCESS 0
# define ERROR 1
# define MAX_PHILOS 200

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
}   t_state;

// Structure for each philosopher
typedef struct s_philo
{
    int             id;             // Philosopher number (1 to n)
    int             meals_eaten;    // Number of times the philosopher has eaten
    long long       last_meal;      // Timestamp of last meal
    t_state         state;          // Current state of the philosopher
    pthread_t       thread;         // Thread ID
    pthread_mutex_t *left_fork;     // Left fork mutex
    pthread_mutex_t *right_fork;    // Right fork mutex
    struct s_data   *data;          // Pointer to shared data
}   t_philo;

// Structure for shared data
typedef struct s_data
{
    int             num_philos;     // Number of philosophers
    int             time_to_die;    // Time until death (ms)
    int             time_to_eat;    // Time to eat (ms)
    int             time_to_sleep;  // Time to sleep (ms)
    int             must_eat;       // Number of times each philo must eat (-1 if infinite)
    bool            someone_died;    // Flag to check if simulation should stop
    long long       start_time;     // Start time of simulation
    pthread_mutex_t *forks;         // Array of fork mutexes
    pthread_mutex_t print_mutex;    // Mutex for printing messages
    pthread_mutex_t death_mutex;    // Mutex for checking death condition
    t_philo         *philosophers;  // Array of philosopher structures
}   t_data;


//init.c
int parse_args(t_data *data, int argc, char **argv);
int init_philosophers(t_data *data);
int init_mutex(t_data *data);
int init_data (t_data *data, int argc, char **argv);

//check_args
int	is_valid_number(char *str);
int	check_limits(char *str);
int	check_philo_number(char *str);
void	check_min_values(char **argv);
int	check_args(int argc, char **argv);

//main.c

//monitor.c
bool	all_ate_enough(t_data *data);
void	*monitor_routine(void *data_void);

//routines.c
int take_forks(t_philo *philo);
void drop_forks(t_philo *philo);
int eat(t_philo *philo);
int	sleep_and_think(t_philo *philo);
void	*philosopher_routine(void *philosopher_void);


//status.c
bool	check_death(t_data *data);
void print_status(t_philo *philo, t_state state);
void	clean_up(t_data *data);

//time.c
long long time_diff(long long past, long long present);
void precise_sleep(long long time);
long long get_time(void);

//utils.c
int	ft_atoi(const char *str);
int error_msg(char *str);


#endif