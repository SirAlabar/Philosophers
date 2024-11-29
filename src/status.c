/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/29 19:21:43 by hluiz-ma         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		time = time_diff(philo->data->start_time, get_time());
		if (state == FORK_TAKEN)
			printf(WHITE "%4lld " RESET BOLD "%2i " GREEN "%16s %s\n" RESET,
				time, philo->id, "has taken a fork", "🍴");
		else if (state == EATING)
			printf(WHITE "%4lld " RESET BOLD "%2i " BLUE "%16s %s\n" RESET,
				time, philo->id, "is eating", "🍝");
		else if (state == SLEEPING)
			printf(WHITE "%4lld " RESET BOLD "%2i " CYAN "%16s %s\n" RESET,
				time, philo->id, "is sleeping", "😴");
		else if (state == THINKING)
			printf(WHITE "%4lld " RESET BOLD "%2i " MAGENTA "%16s %s\n" RESET,
				time, philo->id, "is thinking", "💭");
		else if (state == DIED)
			printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET, time,
				philo->id, "died", "💀");
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

/*
void	print_status(t_philo *philo, t_state state)
{
	int	i;
	int	i;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		time = time_diff(philo->data->start_time, get_time());
		if (state == FORK_TAKEN)
			printf("%lld %d has taken a fork\n", time, philo->id);
		else if (state == EATING)
			printf("%lld %d is eating\n", time, philo->id);
		else if (state == SLEEPING)
			printf("%lld %d is sleeping\n", time, philo->id);
		else if (state == THINKING)
			printf("%lld %d is thinking\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}*/
void	clean_up(t_data *data)
{
	int i;
	
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
