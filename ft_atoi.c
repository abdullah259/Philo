/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:38:21 by omar              #+#    #+#             */
/*   Updated: 2022/08/23 14:42:48 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	free_exit(t_data *data)
{
	ag_free(data);
	ag_exit();
}

int	ft_atoi(char *str, t_data *data)
{
	int				i;
	int				pon;
	unsigned long	num;

	num = 0;
	i = 0;
	pon = 1;
	if (str[i] == '-' || str[i] == '+')
		pon *= 1 - 2 * (str[i++] == '-');
	if (!is_digit(str[i]))
		free_exit(data);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		if (num > 2147483648 && pon == -1)
			free_exit(data);
		else if (num > 2147483647 && pon == 1)
			free_exit(data);
		i++;
	}
	return ((int)(pon * num));
}
