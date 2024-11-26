
#include "philosophers.h"

int parse_args(t_data *data, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (error_msg("wrong number of arguments"));
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat = -1;
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    if(data->num_philos <= 0 || data->time to die <= 0
    || data->time_to_eat <= 0 || data->time_to_sleep <= 0|
    || (argv == 6 && data->must_eat <= 0))
        return(error_msg("invalid argument values."));
    return (SUCESS);    
}

int init_data (t_data *data, int argc, char **argv)
{
    if(parse_args(data, argc, argv) != SUCESS)
        return(ERROR);
    data->someone_died = false;
    data->start_time = get_time();
    if(data->start_time < 0)
        return(ERROR);
    data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
    if(!data->philosophers)
        return(error_msg("malloc failed for philosophers"));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if(!data->forks)
    {
        free(data->philosophers);
        return (error_msg("malloc failed for forks"));
    }
    return (SUCESS);
}

int init_mutex(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->num_philos)
    {
        if(pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while(--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            return(error_msg("mutex initialization failed"));
        }
    }
    if(pthread_mutex_init(&data->print_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&data->print_mutex);        
        i = -1;
        while(++i < data->num_philos)
            pthread_mutex_destroy(&data->forks[i]);
        return (error_msg("death mutex initialization failed"));   
    }
    return (SUCESS);
}

int init_philosophers(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->num_philos)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].last_meal = data->start_time;
        data->philosophers[i].state = THINKING;
        data->philosophers[i].data = data;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philos];
    }
    return (SUCESS);
}