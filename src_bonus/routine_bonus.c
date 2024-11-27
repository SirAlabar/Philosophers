#include "../include/philosophers_bonus.h"

int take_forks(t_philo *philo)
{
    sem_wait(philo->data->forks); 
    print_status(philo, FORK_TAKEN);
    sem_wait(philo->data->forks);
    print_status(philo, FORK_TAKEN);
    return (SUCCESS);
}

int eat(t_philo *philo)
{
    print_status(philo, EATING);
    philo->last_meal = get_time();
    precise_sleep(philo->data->time_to_eat);
    philo->meals_eaten++;
    sem_post(philo->data->forks);
    sem_post(philo->data->forks); 
    return (SUCCESS);
}

int sleep_and_think(t_philo *philo)
{
    print_status(philo, SLEEPING);
    precise_sleep(philo->data->time_to_sleep);
    print_status(philo, THINKING);
    return (SUCCESS);
}

void philosopher_routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
        usleep(100);
    while (1)
    {
        take_forks(philo);
        eat(philo);
        sleep_and_think(philo);
        if (philo->data->must_eat != -1 && 
            philo->meals_eaten >= philo->data->must_eat)
            exit(SUCCESS);
        usleep(100);
    }
}