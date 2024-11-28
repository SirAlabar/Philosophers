/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:59:41 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 19:36:03 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_args(data, argc, argv) != SUCCESS)
		return (ERROR);
	data->someone_died = false;
	data->start_time = get_time();
	if (data->start_time < 0)
		return (ERROR);
	data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philosophers)
		return (error_msg("malloc failed for philosophers"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free(data->philosophers);
		return (error_msg("malloc failed for forks"));
	}
	return (SUCCESS);
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_forks(data, i);
			return (error_msg("mutex initialization failed"));
		}
	}
	return (SUCCESS);
}

int	init_mutex(t_data *data)
{
	if (init_fork_mutexes(data) != SUCCESS)
		return (ERROR);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		destroy_forks(data, data->num_philos);
		return (error_msg("print mutex initialization failed"));
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks(data, data->num_philos);
		return (error_msg("death mutex initialization failed"));
	}
	if (pthread_mutex_init(&data->last_meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks(data, data->num_philos);
		return (error_msg("last_meal mutex initialization failed"));
	}
	return (SUCCESS);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal = data->start_time;
		data->philosophers[i].state = THINKING;
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->num_philos];
	}
	return (SUCCESS);
}
