/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:57:29 by aghazi            #+#    #+#             */
/*   Updated: 2022/10/02 01:57:30 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int				i;
	int				pon;
	unsigned long	num;

	num = 0;
	i = 0;
	pon = 1;
	if (str[i] == '-' || str[i] == '+')
		pon *= 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		if (num > 2147483648 && pon == -1)
			return (-1);
		else if (num > 2147483647 && pon == 1)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		if (!is_digit(str[i]))
			return (-1);
	return ((int)(pon * num));
}
