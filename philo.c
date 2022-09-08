/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/09/06 18:00:42 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *ph)
{
	if (get_time() - ph->general_info->start_time > ph->general_info->time_to_die)
		return (0);
	return (1);
}

void	*start(void *philo)
{
	t_philo *ph = (t_philo *)philo;

	while (1) // while everyone still alive
	{
		while (take_forks(ph))
			usleep(500);
		printf("phlio no %d started eating \n", ph->philo_id);
		sleep(14);
		ph->general_info->start_time = get_time();
		// usleep(ph->general_info->time_to_eat);
		if (!is_alive(&ph))
			return (0);
		drop_forks(ph);
		printf("phlio no %d is sleeping \n", ph->philo_id);
		sleep(14);
		// usleep(ph->general_info->time_to_sleep);
		usleep(500);
		if (!is_alive(&ph))
			return (0);
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

long	get_time()//change it to milliseconds
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return(current_time.tv_sec * 1000 + (long)(current_time.tv_usec / 1000));
}

int	main(int arc, char **argv)
{
	t_philo philos[200];
	t_info  info;
	int i;
	// long start_time;// add it in gernal sturct
	info.start_time = get_time();

	printf("start = %ld\n", get_time() - info.start_time);
	sleep(5);
	printf("start = %ld\n", get_time() - info.start_time);
	i = 0;
	philos->right_fork = 0;
	philos->left_fork = 0;	
	pthread_t life_thread;
	if (arc == 5 || arc == 6)
	{
		if (parse_input(arc, argv, &info))
			return (1);
		if (init_philos(philos, &info))
			return (1);
		// simulation_start_time = gettimeofday();
		while (i < info.no_of_philos)
		{
			philos[i].general_info = &info;
			philos[i].philo_id = i;
			pthread_create(&life_thread, NULL, &start, &philos[i]);
			i++;
		}
		while (info.no_of_philos)
		{
			pthread_join(life_thread, NULL);
			info.no_of_philos--;
		}
		// printf("flag = %d \n", info.death_flag);
	}
	return (0);
}