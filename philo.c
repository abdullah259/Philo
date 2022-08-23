/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/08/23 18:59:14 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


void    *start(void *philo)
{
    
    t_philo *ph = (t_philo *)philo;
    
    //lock right fork && check fork value
    //if free pick fork.
    //lock left fork && check fork value
    //if free pick fork.

    
    return NULL;
}

int main(int arc, char **argv)
{
    t_philo philos[200];
    t_info  info;
    int i;
    info.death_flag = 0;
    i = 0;
    pthread_t life_thread;
    pthread_mutex_init(&info.mutex1, NULL);
    if (arc == 5 || arc == 6)
    {
        info.no_of_philos = atoi(argv[1]);
        info.time_to_die = atoi(argv[2]);
        info.time_to_eat = atoi(argv[3]);
        info.time_to_sleep = atoi(argv[4]);
        
        if(arc == 6)
            info.no_of_times_eat = atoi(argv[5]);
        while (i < info.no_of_philos)
        {
            philos[i].general_info = &info;
            philos[i].philo_id = i;
            pthread_create(&life_thread, NULL, &start, &philos[i]);
            i++;
        }
        while(info.no_of_philos)
        {
            pthread_join(life_thread, NULL);
            info.no_of_philos--;
        }
        printf("flag = %d \n", info.death_flag);
    }
    return (0);
}