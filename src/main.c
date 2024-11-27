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

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != SUCCESS)
		return (ERROR);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (ERROR);
	if (init_mutex(&data) != SUCCESS)
	{
		clean_up(&data);
		return (ERROR);
	}
	if (init_philosophers(&data) != SUCCESS)
	{
		clean_up(&data);
		return (ERROR);
	}
	printf("Initialization successful with:\n");
	printf("Philosophers: %d\n", data.num_philos);
	printf("Time to die: %d\n", data.time_to_die);
	printf("Time to eat: %d\n", data.time_to_eat);
	printf("Time to sleep: %d\n", data.time_to_sleep);
	if (argc == 6)
		printf("Must eat count: %d\n", data.must_eat);
	clean_up(&data);
	return (SUCCESS);
}
