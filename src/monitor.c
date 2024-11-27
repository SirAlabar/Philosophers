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
   t_data *data = (t_data *)data_void;
   int i;
   long long time;

   while (1)
   {
       i = -1;
       while (++i < data->num_philos)
       {
           time = time_diff(data->philosophers[i].last_meal, get_time());
           if (time >= data->time_to_die && !check_death(data))
           {
               pthread_mutex_lock(&data->death_mutex);
               data->someone_died = true;
               pthread_mutex_unlock(&data->death_mutex);
               printf("%lld %d died\n", time_diff(data->start_time, get_time()), data->philosophers[i].id);
               return (NULL);
           }
       }
       usleep(50);
       if (check_death(data))
           return (NULL);
   }
}
