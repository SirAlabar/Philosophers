/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:22:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/11/26 19:22:40 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_limits(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	check_philo_number(char *str)
{
	int	num;

	num = ft_atoi(str);
	if (num < 1)
		return (error_msg("need at least 1 philosopher"));
	if (num > MAX_PHILOS)
		return (error_msg("too many philosophers (max 200)"));
	return (SUCCESS);
}

void	check_min_values(char **argv)
{
	if (ft_atoi(argv[2]) < 61)
		printf("%sWarning: time_to_die below 60ms might cause timing issues%s\n",
			YELLOW, RESET);
	if (ft_atoi(argv[3]) < 61)
		printf("%sWarning: time_to_eat below 60ms might cause timing issues%s\n",
			YELLOW, RESET);
	if (ft_atoi(argv[4]) < 61)
		printf("%sWarning: time_to_sleep below 60ms might cause timing issues%s\n",
			YELLOW, RESET);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error_msg("wrong number of arguments"));
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (error_msg("invalid argument format"));
		if (!check_limits(argv[i]))
			return (error_msg("argument too large"));
		i++;
	}
	if (check_philo_number(argv[1]) != SUCCESS)
		return (ERROR);
	check_min_values(argv);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (error_msg("meals number must be positive"));
	return (SUCCESS);
}
