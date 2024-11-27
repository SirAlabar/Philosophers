#include "../include/philosophers_bonus.h"

void start_philosopher(t_philo *philo)
{
    pthread_t monitor;

    philo->last_meal = get_time();\
    if(pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
    {
        printf("Error: failed to create monitor thread\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(monitor);
    philosopher_routine(philo);
    exit(EXIT_SUCCESS);
}

int create_process(t_data *data)
{
    int i;

    data->start_time = get_time();
    if(data->start_time < 0)
        return (ERROR);

    i = -1;
    while(++i < data->num_philos)
    {
        data->philosophers[i].last_meal = data->start_time;
        data->philosophers[i].pid = fork();
        if(data->philosophers[i].pid < 0)
            return (error_msg("fork_failed"));
        if (data->philosophers[i].pid == 0)
            start_philosopher(&data->philosophers[i]);
    }
    return (SUCCESS);
}

void wait_process(t_data *data)
{
    int i;
    int status;

    i = -1;
    while(++i < data->num_philos)
    {
        waitpid(-1, &status, 0);
        if(WEXITSTATUS(status) == EXIT_FAILURE)
        {
            kill_processes(data);
            break;
        }
    }
}

int handle_one_philo(t_data *data)
{
    data->start_time = get_time();
    data->philosophers[0].last_meal = data->start_time;
    sem_wait(data->print);
    print_status(&data->philosophers[0], FORK_TAKEN);
    precise_sleep(data->time_to_die);
    print_status(&data->philosophers[0], DIED);
    sem_post(data->forks);
    return (SUCCESS);
}

int main(int argc, char **argv)
{
    t_data data;

    if (check_args(argc, argv) != SUCCESS)
        return (ERROR);
    if (init_data(&data, argc, argv) != SUCCESS)
        return (ERROR);
    if (data.num_philos == 1)
        handle_one_philo(&data);
    else
    {
        if (create_process(&data) != SUCCESS)
        {
            clean_up(&data);
            return (ERROR);
        }
        wait_process(&data);
    }
    clean_up(&data);
    return (SUCCESS);
}
