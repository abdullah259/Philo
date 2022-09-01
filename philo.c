/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghazi <aghazi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:10:22 by aghazi            #+#    #+#             */
/*   Updated: 2022/09/01 20:09:36 by aghazi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int drop_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right_mutex);
    *philo->right_fork = 0;
    printf("phlio no %d droped right fork \n", philo->philo_id);
    pthread_mutex_unlock(philo->right_mutex);
    pthread_mutex_lock(philo->left_mutex);
    *philo->left_fork = 0;
    printf("phlio no %d droped left fork \n", philo->philo_id);
    pthread_mutex_unlock(philo->left_mutex);

    return (0);
}


int take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right_mutex);
    if (*(philo->right_fork) == 0)
    {
        *(philo->right_fork) = 1;
        pthread_mutex_unlock(philo->right_mutex);
        pthread_mutex_lock(philo->left_mutex);
        if (*(philo->left_fork) == 0)
        {
            *(philo->left_fork) = 1;
            printf("phlio no %d picked right fork \n", philo->philo_id);
            printf("phlio no %d picked LEFT fork \n", philo->philo_id);
            pthread_mutex_unlock(philo->left_mutex);
            return (0);
        }
        else
        {
            pthread_mutex_unlock(philo->left_mutex);
            pthread_mutex_lock(philo->right_mutex);
            // printf("phlio no %d place back right fork \n", philo->philo_id);
            
            *(philo->right_fork) = 0;
        }
    }
    pthread_mutex_unlock(philo->right_mutex);
    return (1);
}

void    *start(void *philo)
{
    
    t_philo *ph = (t_philo *)philo;

    while (1)// while everyone still alive
    {
        while (take_forks(ph))
            usleep(500);
        printf("phlio no %d started eating \n", ph->philo_id);
        sleep(14);
        // usleep(ph->general_info->time_to_eat);
        drop_forks(ph);
        printf("phlio no %d is sleeping \n", ph->philo_id);
        sleep(14);
        // usleep(ph->general_info->time_to_sleep);
        usleep(500);
    }
    
    
    
    return NULL;
}

int init_mutex(t_philo *ph, t_info *info)
{
    int i;

    i = 0;

    while(i < info->no_of_philos)
    {
        if (pthread_mutex_init(&info->mutex[i], NULL) != 0)
            return (1);
        i++;
    }
    i = 0;
    while (i < info->no_of_philos)
    {
        ph[i].right_mutex = &info->mutex[i];
        if (i == 0)
            ph[i].left_mutex = &info->mutex[info->no_of_philos - 1];
        else
            ph[i].left_mutex = &info->mutex[i - 1];
        i++;
    }
    return (0);
}

int init_forks(t_philo *ph, t_info *info)
{
    int i;

    i = 0;
    info->forks = calloc(info->no_of_philos,sizeof(int));
    while (i < info->no_of_philos)
    {
        ph[i].right_fork = &info->forks[i];
        if (i == 0)
            ph[i].left_fork = &info->forks[info->no_of_philos - 1];
        else
            ph[i].left_fork = &info->forks[i - 1];
        i++;
    }
    return (0);
}

int init_philos(t_philo *ph, t_info *info)
{
    if (init_mutex(ph, info))
        return (1);
    if (init_forks(ph, info))
        return (1);
    return (0);
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
long    get_time()//change it to milliseconds
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    return(current_time.tv_sec * 1000 + (long)(current_time.tv_usec *0.001));
}
int main(int arc, char **argv)
{
    t_philo philos[200];
    t_info  info;
    int i;
    long start_time;// add it in gernal sturct
    
    start_time = get_time();

    printf("start = %ld\n", get_time() - start_time);
    sleep(5);
    printf("start = %ld\n", get_time() - start_time);


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
        while(info.no_of_philos)
        {
            pthread_join(life_thread, NULL);
            info.no_of_philos--;
        }
        // printf("flag = %d \n", info.death_flag);
    }
    return (0);
}