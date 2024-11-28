/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 22:15:01 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	all_ate_enough(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat == -1)
		return (false);
	finished = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		if (data->philosophers[i].meals_eaten >= data->must_eat)
			finished++;
	}
	return (finished == data->num_philos);
}

bool	check_philosopher_death(t_data *data, int i)
{
	long long	time;

	pthread_mutex_lock(&data->last_meal_mutex);
	time = time_diff(data->philosophers[i].last_meal, get_time());
	pthread_mutex_unlock(&data->last_meal_mutex);
	if (time >= data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = true;
			pthread_mutex_lock(&data->print_mutex);
			printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET, time,
				data->philosophers[i].id, "died", "💀");
			pthread_mutex_unlock(&data->print_mutex);
		}
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	return (false);
}

bool	check_simulation_end(t_data *data)
{
	if (data->must_eat != -1 && all_ate_enough(data))
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *data_void)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_void;
	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
		}
		if (check_simulation_end(data))
			return (NULL);
		usleep(50);
		if (check_death(data))
			return (NULL);
	}
}
