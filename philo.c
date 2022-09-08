/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/09/08 20:51:01 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *ph)
{
	if (get_time() - ph->start_eat >= ph->general_info->time_to_die)
		return (0);
	return (1);
}

void	*start(void *philo)
{
	t_philo *ph = (t_philo *)philo;

	while (1 && ph->general_info->death_flag == 0)
	{
		if (ph->general_info->death_flag == 0)
		{
			while (take_forks(ph) && ph->general_info->death_flag == 0) // check here if phil is alive or not
				if (!ag_usleep(ph->general_info->time_to_eat,ph))
                    exit(0);
			printf("%ld phlio no %d started eating \n",get_time() - ph->general_info->start_time, ph->philo_id);
			ph->start_eat = get_time();
			if (!ag_usleep(ph->general_info->time_to_eat,ph))
                exit(0);
			drop_forks(ph);
			printf("%ld phlio no %d is sleeping \n",get_time() - ph->general_info->start_time , ph->philo_id);
			if (!ag_usleep(ph->general_info->time_to_eat,ph))
                exit(0);
			printf("Thinking\n");
		}
		// if (ph->general_info->death_flag == 1)
		// {
		// 	printf("philo is dead\n");
		// 	break;
		// }
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
	// sleep(5);
    // ag_usleep(5000,philos);
	// printf("start = %ld\n", get_time() - info.start_time);
	i = 0;
<<<<<<< HEAD
	philos->right_fork = 0;
	philos->left_fork = 0;	
	pthread_t life_thread;
=======
	pthread_t *life_thread; // 

    life_thread = malloc(sizeof(pthread_t) * info.no_of_philos);    
>>>>>>> 0574868d461fd2ad25accc3aa5f5934192344946
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
			pthread_create(&life_thread[i], NULL, &start, &philos[i]);
			i++;
		}
		while (info.no_of_philos)
		{
			pthread_join(life_thread[i], NULL);
			info.no_of_philos--;
		}
	}
	return (0);
}