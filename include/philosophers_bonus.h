/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/27 19:22:40 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write, usleep, fork
# include <sys/time.h>   // gettimeofday
# include <sys/wait.h>   // waitpid
# include <fcntl.h>      // For O_* constants
# include <sys/stat.h>   // For mode constants
# include <semaphore.h>  // sem_open, sem_close, sem_post, sem_wait, sem_unlink
# include <signal.h>     // kill
# include <pthread.h>    // pthread functions for monitor thread
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

// Semaphore names
# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_DEATH "/philo_death"
# define SEM_MEALS "/philo_meals"

// Philosopher states
typedef enum e_state
{
    THINKING,
    EATING,
    SLEEPING,
    FORK_TAKEN,
    DIED
} t_state;

// Structure for each philosopher
typedef struct s_philo
{
    int             id;             // Philosopher number (1 to n)
    int             meals_eaten;    // Number of times the philosopher has eaten
    long long       last_meal;      // Timestamp of last meal
    t_state         state;          // Current state of the philosopher
    pid_t           pid;            // Process ID
    struct s_data   *data;          // Pointer to shared data
} t_philo;

// Structure for shared data
typedef struct s_data
{
    int             num_philos;     // Number of philosophers
    int             time_to_die;    // Time until death (ms)
    int             time_to_eat;    // Time to eat (ms)
    int             time_to_sleep;  // Time to sleep (ms)
    int             must_eat;       // Number of times each philo must eat (-1 if infinite)
    bool            someone_died;   // Flag to check if simulation should stop
    long long       start_time;     // Start time of simulation
    sem_t           *forks;         // Semaphore for forks
    sem_t           *print;         // Semaphore for printing
    sem_t           *death;         // Semaphore for death check
    sem_t           *meals;         // Semaphore for meals count
    t_philo         *philosophers;  // Array of philosopher structures
} t_data;