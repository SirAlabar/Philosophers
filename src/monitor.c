/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:40 by hluiz-ma         ###   ########.fr       */
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

void	*monitor_routine(void *data_void)
{
	t_data		*data;
	int			i;
	long long	time_since_meal;

	data = (t_data *)data_void;
	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			time_since_meal = time_diff(data->philosophers[i].last_meal, 
				get_time());
			if (time_since_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				if (!data->someone_died)
				{
					data->someone_died = true;
					print_status(&data->philosophers[i], DIED);
				}
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			if (data->must_eat != -1 && 
				data->philosophers[i].meals_eaten >= data->must_eat)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->someone_died = true;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}
