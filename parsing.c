/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:57:12 by aghazi            #+#    #+#             */
/*   Updated: 2022/10/02 01:57:13 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_after_num(char c, char c1, char c2)
{
	if ((c == '-' || c == '+') && (c1 >= '0' && c1 <= '9')
		&& (c2 == '-' || c2 == '+'))
		return (0);
	if ((c == '-' || c == '+') && (c1 == '\0' || c1 == ' ' || c1 == '\t'))
		return (0);
	if (c1 == '-' || c1 == '+')
		return (0);
	return (1);
}

int	check_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-' || argv[i][j] == '+')
			{
				if (check_after_num(argv[i][j], argv[i][j + 1],
					argv[i][j + 2]) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_input(int ac, char **av, t_info *info)
{
	if (check_valid(av))
	{
		info->no_of_philos = ft_atoi(av[1]);
		if (info->no_of_philos < 0 || info->no_of_philos == 0)
			return (1);
		info->time_to_die = ft_atoi(av[2]);
		if (info->time_to_die < 0 || info->time_to_die == 0)
			return (1);
		info->time_to_eat = ft_atoi(av[3]);
		if (info->time_to_eat < 0 || info->time_to_eat == 0)
			return (1);
		info->time_to_sleep = ft_atoi(av[4]);
		if (info->time_to_sleep < 0 || info->time_to_sleep == 0)
			return (1);
		if (ac == 6)
		{
			info->no_of_times_eat = ft_atoi(av[5]);
			if (info->no_of_times_eat < 0 || info->no_of_times_eat == 0)
				return (1);
		}
		if (info->no_of_philos > 200)
			return (1);
		return (0);
	}
	return (1);
}

int	check_flag(t_philo *ph, int *i)
{
	if (ph->general_info->no_of_times_eat == 0 || (*i) > 0)
		return (1);
	return (0);
}
