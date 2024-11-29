/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:59:24 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/28 18:59:25 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	print_status(t_philo *philo, t_state state)
{
	long long	time;

	sem_wait(philo->data->print);
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
	if (state != DIED)
		sem_post(philo->data->print);
}
