/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 18:59:50 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
		usleep(100);
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN);
	}
	return (SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	eat(t_philo *philo)
{
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	precise_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	drop_forks(philo);
	return (SUCCESS);
}

int	sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_sleep(philo->data->time_to_sleep);
	print_status(philo, THINKING);
	return (SUCCESS);
}

void	*philosopher_routine(void *philosopher_void)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher_void;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!check_death(philo->data))
	{
		if (take_forks(philo) != SUCCESS)
			break ;
		if (eat(philo) != SUCCESS)
			break ;
		if (sleep_and_think(philo) != SUCCESS)
			break ;
		usleep(100);
	}
	return (NULL);
}
