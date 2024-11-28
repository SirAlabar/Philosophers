/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:59:54 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 21:58:47 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	precise_sleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (error_msg("gettimeofday() failed"));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
