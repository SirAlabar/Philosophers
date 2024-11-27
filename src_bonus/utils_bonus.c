#include "../include/philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sing;
	int	res;

	i = 0;
	sing = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sing);
}

int error_msg(char *str)
{
    printf("%s Error: %s%s\n", RED, str, RESET);
    return (ERROR);
}

void clean_semaphores(void)
{
    sem_unlink(SEM_FORKS);
    sem_unlink(SEM_PRINT);
    sem_unlink(SEM_DEATH);
    sem_unlink(SEM_MEALS);
}

void clean_up(t_data *data)
{
    if (data->philosophers)
    {
        kill_processes(data);
        free(data->philosophers);
    }
    if (data->forks)
        sem_close(data->forks);
    if (data->print)
        sem_close(data->print);
    if (data->death)
        sem_close(data->death)
    if (data->meals)
        sem_close(data->meals);
    clean_semaphores();
}

void kill_processes(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->num_philos)
    {
        if (data->philosophers[i].pid > 0)
            kill(data->philosophers[i].pid, SIGKILL);
    }
    while(i--)
        waitpid(-1, NULL, 0);
}