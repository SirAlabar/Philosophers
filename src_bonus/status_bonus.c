
#include "../include/philosophers_bonus.h"

void print_status(t_philo *philo, t_state state)
{
    sem_wait(philo->data->print);
    if (state == FORK_TAKEN)
    printf(GREEN"%lld %d has taken a fork %s\n"RESET, 
        time_diff(philo->data->start_time, get_time()), philo->id, "🍴");
    else if (state == EATING)
    printf(YELLOW"%lld %d is eating %s\n"RESET, 
        time_diff(philo->data->start_time, get_time()), philo->id, "🍝");
    else if (state == SLEEPING)
    printf(BLUE"%lld %d is sleeping %s\n"RESET, 
        time_diff(philo->data->start_time, get_time()), philo->id, "😴");
    else if (state == THINKING)
    printf(CYAN"%lld %d is thinking %s\n"RESET, 
        time_diff(philo->data->start_time, get_time()), philo->id, "💭");
    if (state != DIED)
    sem_post(philo->data->print);
}
