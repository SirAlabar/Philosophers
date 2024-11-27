/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/27 19:22:40 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_death(t_data *data)
{
	bool	died;

	pthread_mutex_lock(&data->death_mutex);
	died = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (died);
}

void print_status(t_philo *philo, t_state state)
{
    long long time;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (!check_death(philo->data))
    {
        time = time_diff(philo->data->start_time, get_time());
        if (state == FORK_TAKEN)
			printf("%lld %d has taken a fork\n", time, philo->id);
		else if (state == EATING)
			printf("%lld %d is eating\n", time, philo->id);
		else if (state == SLEEPING)
			printf("%lld %d is sleeping\n", time, philo->id);
		else if (state == THINKING)
			printf("%lld %d is thinking\n", time, philo->id);
		else if (state == DIED)
			printf("%lld %d died\n", time, philo->id);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void	clean_up(t_data *data)
{
	int	i;

	if (data->philosophers)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		free(data->philosophers);
		free(data->forks);
        data->philosophers = NULL;
        data->forks = NULL;		
	}
}
