/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:57:21 by aghazi            #+#    #+#             */
/*   Updated: 2022/10/02 01:57:22 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_alive(t_philo *ph)
{
	if (get_time() - ph->start_eat >= ph->general_info->time_to_die)
	{
		print_status(ph, 'd');
		ph->general_info->death_flag = 1;
	}
}

void	check_i(int *i)
{
	if (*i > 0)
		(*i)--;
}

void	*start(void *philo)
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)philo;
	ph->start_eat = get_time();
	i = ph->general_info->no_of_times_eat;
	while (ph->general_info->death_flag == 0 && check_flag(ph, &i))
	{
		while (ph->general_info->death_flag == 0 && take_forks(ph))
		{
			usleep(100);
			is_alive(ph);
		}
		print_status(ph, 'e');
		ph->start_eat = get_time();
		ag_usleep(ph->general_info->time_to_eat, ph);
		if (ph->general_info->death_flag == 1)
			break ;
		drop_forks(ph);
		print_status(ph, 's');
		ag_usleep(ph->general_info->time_to_sleep, ph);
		print_status(ph, 't');
		check_i(&i);
	}
	return (NULL);
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
	pthread_t	*life_thread;
	t_philo		philos[200];
	t_info		info;
	int			i;

	i = 0;
	ft_init(&info);
	if (arc == 5 || arc == 6)
	{
		life_thread = ft_calloc(200, sizeof(pthread_t));
		if (parse_input(arc, argv, &info))
			return (1);
		info.forks = ft_calloc(info.no_of_philos, sizeof(t_forks));
		if (init_philos(philos, &info))
			return (1);
		info.start_time = get_time();
		printf("start = %ld\n", get_time() - info.start_time);
		creat_philo(philos, &info, life_thread, start);
		while (i < info.no_of_philos)
		{
			pthread_join(life_thread[i], NULL);
			i++;
		}
	}
	return (0);
}
