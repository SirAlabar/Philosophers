/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/27 19:22:40 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	while (++i < data->num_philos)
	{
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
	if (start_simulation(&data) != SUCCESS)
		return (clean_up(&data), ERROR);
	clean_up(&data);
	return (SUCCESS);
}
