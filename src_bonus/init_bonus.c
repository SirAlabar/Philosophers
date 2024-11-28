/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:59:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 18:59:14 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	parse_args(t_data *data, int argc, char **argv)
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
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->must_eat <= 0))
		return (error_msg("invalid argument values."));
	return (SUCCESS);
}

int	init_semaphores(t_data *data)
{
	clean_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		return (error_msg("failed to create forks semaphore"));
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (error_msg("failed to create print semaphore"));
	data->death = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	if (data->death == SEM_FAILED)
		return (error_msg("failed to create death semaphores"));
	data->meals = sem_open(SEM_MEALS, O_CREAT, 0644, 1);
	if (data->meals == SEM_FAILED)
		return (error_msg("failed to create meals semaphores"));
	return (SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_args(data, argc, argv) != SUCCESS)
		return (ERROR);
	data->someone_died = false;
	data->start_time = get_time();
	if (data->start_time < 0)
		return (ERROR);
	if (init_philosophers(data) != SUCCESS)
		return (ERROR);
	if (init_semaphores(data) != SUCCESS)
	{
		free(data->philosophers);
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philosophers)
		return (error_msg("malloc failed for philosophers"));
	i = -1;
	while (++i < data->num_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal = data->start_time;
		data->philosophers[i].state = THINKING;
		data->philosophers[i].data = data;
		data->philosophers[i].pid = 0;
	}
	return (SUCCESS);
}
