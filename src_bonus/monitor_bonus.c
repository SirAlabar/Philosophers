/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:59:18 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 19:04:45 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

bool	check_death(t_data *data)
{
	bool	died;

	sem_wait(data->death);
	died = data->someone_died;
	sem_post(data->death);
	return (died);
}

bool	all_ate_enough(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat == -1)
		return (false);
	sem_wait(data->meals);
	finished = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		if (data->philosophers[i].meals_eaten >= data->must_eat)
			finished++;
	}
	sem_post(data->meals);
	return (finished == data->num_philos);
}

void	*monitor_routine(void *philosopher_void)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)philosopher_void;
	while (1)
	{
		sem_wait(philo->data->death);
		time = time_diff(philo->last_meal, get_time());
		if (time >= philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf(RED "%lld %d died %s" RESET "\n",
				time_diff(philo->data->start_time, get_time()), philo->id, "💀");
			sem_post(philo->data->death);
			exit(EXIT_FAILURE);
		}
		sem_post(philo->data->death);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
			exit(EXIT_SUCCESS);
		usleep(100);
	}
	return (NULL);
}
