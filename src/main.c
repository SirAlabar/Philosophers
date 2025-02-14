/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 22:20:19 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->num_philos)
	{
		data->philosophers[i].last_meal = data->start_time;
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
			return (error_msg("thread creation failed"));
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (error_msg("monitor thread creation failed"));
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philosophers[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (SUCCESS);
}

static int	handle_one_philo(t_data *data)
{
	long long	time;

	time = get_time();
	data->start_time = get_time();
	data->philosophers[0].last_meal = data->start_time;
	print_status(&data->philosophers[0], FORK_TAKEN);
	precise_sleep(data->time_to_die);
	printf(WHITE "%4lld " RESET BOLD "%2i " RED "%16s %s\n" RESET, time,
		data->philosophers[0].id, "died", "💀");
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != SUCCESS)
		return (ERROR);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (ERROR);
	if (init_mutex(&data) != SUCCESS)
		return (clean_up(&data), ERROR);
	if (init_philosophers(&data) != SUCCESS)
		return (clean_up(&data), ERROR);
	if (data.num_philos == 1)
		handle_one_philo(&data);
	else if (start_threads(&data) != SUCCESS)
		return (clean_up(&data), ERROR);
	clean_up(&data);
	return (SUCCESS);
}
