/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 18:59:52 by hluiz-ma         ###   ########.fr       */
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

void	print_status(t_philo *philo, t_state state)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo->data))
	{
		time = time_diff(philo->data->start_time, get_time());
		if (state == FORK_TAKEN)
			printf(GREEN "%lld %d has taken a fork %s\n" RESET, time, philo->id,
				"🍴");
		else if (state == EATING)
			printf(YELLOW "%lld %d is eating %s\n" RESET, time, philo->id, "🍝");
		else if (state == SLEEPING)
			printf(BLUE "%lld %d is sleeping %s\n" RESET, time, philo->id, "😴");
		else if (state == THINKING)
			printf(CYAN "%lld %d is thinking %s\n" RESET, time, philo->id, "💭");
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
		pthread_mutex_destroy(&data->last_meal_mutex);
		free(data->philosophers);
		free(data->forks);
		data->philosophers = NULL;
		data->forks = NULL;
	}
}
