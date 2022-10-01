/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:57:32 by aghazi            #+#    #+#             */
/*   Updated: 2022/10/02 01:57:33 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creat_philo(t_philo *philos, t_info *info,
		pthread_t *life_thread, void *start)
{
	int	i;

	i = 0;
	while (i < info->no_of_philos)
	{
		philos[i].general_info = info;
		philos[i].philo_id = i;
		pthread_create(&life_thread[i], NULL, start, &philos[i]);
		i++;
		usleep(100);
	}
}
