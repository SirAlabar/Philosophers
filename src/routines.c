/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 21:53:18 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(philo, FORK_TAKEN);
	pthread_mutex_lock(second);
	print_status(philo, FORK_TAKEN);
	return (SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

int	eat(t_philo *philo)
{
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	philo->meals_eaten++;
	precise_sleep(philo->data->time_to_eat);
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
		usleep(1000);
	while (!check_death(philo->data))
	{
		if (take_forks(philo) != SUCCESS)
			break ;
		if (eat(philo) != SUCCESS)
			break ;
		if (sleep_and_think(philo) != SUCCESS)
			break ;
		usleep(200);
	}
	return (NULL);
}
