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

# define SUCCESS 0
# define ERROR 1

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
