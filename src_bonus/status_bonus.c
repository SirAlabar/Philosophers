
#include "../include/philosophers_bonus.h"

void print_status(t_philo *philo, t_state state)
{
    sem_wait(philo->data->print);
    if (state == FORK_TAKEN)
        printf("%lld %d has taken a fork\n", 
            time_diff(philo->data->start_time, get_time()), philo->id);
    else if (state == EATING)
        printf("%lld %d is eating\n", 
            time_diff(philo->data->start_time, get_time()), philo->id);
    else if (state == SLEEPING)
        printf("%lld %d is sleeping\n", 
            time_diff(philo->data->start_time, get_time()), philo->id);
    else if (state == THINKING)
        printf("%lld %d is thinking\n", 
            time_diff(philo->data->start_time, get_time()), philo->id);
    else if (state == DIED)
        printf("%lld %d died\n", 
            time_diff(philo->data->start_time, get_time()), philo->id);
    if (state != DIED)
        sem_post(philo->data->print);
}
