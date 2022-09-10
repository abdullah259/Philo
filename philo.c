/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/09/10 10:32:05 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_alive(t_philo *ph)
{
	if (get_time() - ph->start_eat >= ph->general_info->time_to_die)
	{
		ph->general_info->death_flag = 1;
		print_status(ph,'d');
	}
}

void	*start(void *philo)
{
	t_philo *ph = (t_philo *)philo;

	ph->start_eat = ph->general_info->start_time;
	while (ph->general_info->death_flag == 0)
	{
		while (ph->general_info->death_flag == 0 && take_forks(ph))
		{
			usleep(500);
			is_alive(ph);
		}
		if (ph->general_info->death_flag == 1)
		{
			is_alive(ph);
			return NULL;
		}
		print_status(ph,'e');
		ph->start_eat = get_time();
		if (ph->general_info->death_flag == 1)
		{
			is_alive(ph);
			return NULL;
		}
		ag_usleep(ph->general_info->time_to_eat,ph);
		if (ph->general_info->death_flag == 1)
		{
			is_alive(ph);
			return NULL;
		}
		drop_forks(ph);
		print_status(ph, 's');
		ag_usleep(ph->general_info->time_to_sleep,ph); // change here was to to eat || now time to slepp
		print_status(ph, 't');
	}
	return NULL;
}

int parse_input(int ac, char **av, t_info *info)
{
	info->no_of_philos = atoi(av[1]);
	info->time_to_die = atoi(av[2]);
	info->time_to_eat = atoi(av[3]);
	info->time_to_sleep = atoi(av[4]);
	if(ac == 6)
		info->no_of_times_eat = atoi(av[5]);
	return (0);
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

    life_thread = calloc(200,sizeof(pthread_t));
	if (arc == 5 || arc == 6)
	{
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
		}
		i = 0;
		while (i < info.no_of_philos)
		{
			pthread_join(life_thread[i], NULL);
			// info.no_of_philos--;
			i++;
		}
	}
	return (0);
}