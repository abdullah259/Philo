/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/09/27 20:36:33 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_alive(t_philo *ph)
{
	if (get_time() - ph->start_eat >= ph->general_info->time_to_die)
	{
		print_status(ph,'d');
		ph->general_info->death_flag = 1;
	}
}

void	*start(void *philo)
{
	t_philo *ph = (t_philo *)philo;

	ph->start_eat = get_time();
    int i;
    
    i = ph->general_info->no_of_times_eat;
	while (ph->general_info->death_flag == 0 && (ph->general_info->no_of_times_eat == 0 || i > 0))
	{
		while (ph->general_info->death_flag == 0 && take_forks(ph))
		{
			usleep(500);
            is_alive(ph);
		}
		print_status(ph,'e');
		ph->start_eat = get_time();
		ag_usleep(ph->general_info->time_to_eat,ph);
		if (ph->general_info->death_flag == 1)
			break;
		drop_forks(ph);
		print_status(ph, 's');
		ag_usleep(ph->general_info->time_to_sleep,ph);
		print_status(ph, 't');
		usleep(2000);
		if(i > 0)
        	i--;
	}
	return NULL;
}

void	ft_init(t_info *ph)
{
    ph->death_flag = 0;
    ph->no_of_philos = 0;
    ph->no_of_times_eat = 0;
    ph->time_to_die = 0;
    ph->time_to_eat = 0;
    ph->time_to_sleep = 0;
    ph->start_time = 0;
}

int	main(int arc, char **argv)
{
	t_philo philos[200];
	t_info  info;
	int i;
    
    ft_init(&info);
	info.start_time = get_time();
	printf("start = %ld\n", get_time() - info.start_time);

	i = 0;
	pthread_t *life_thread;

	if (arc == 5 || arc == 6)
	{
    	life_thread = ft_calloc(200,sizeof(pthread_t));
		if (parse_input(arc, argv, &info))
			return (1);
		if (init_philos(philos, &info))
			return (1);
		while (i < info.no_of_philos)
		{
			philos[i].general_info = &info;
			philos[i].philo_id = i;
			pthread_create(&life_thread[i], NULL, &start, &philos[i]);
			i++;
            usleep(100);
		}
		i = 0;
		while (i < info.no_of_philos)
		{
			pthread_join(life_thread[i], NULL);
			i++;
		}
	}
	return (0);
}