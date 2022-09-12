#include "philo.h"

int	drop_forks(t_philo *philo)
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

int	 take_forks(t_philo *philo)
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
			printf("%ld phlio no %d picked right fork \n",get_time() - philo->general_info->start_time, philo->philo_id);
			printf("%ld phlio no %d picked Left fork \n",get_time() - philo->general_info->start_time, philo->philo_id);
			// printf("phlio no %d picked LEFT fork \n", philo->philo_id);
			pthread_mutex_unlock(philo->left_mutex);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(philo->left_mutex);
			pthread_mutex_lock(philo->right_mutex);
			*(philo->right_fork) = 0;
		}
	}
	pthread_mutex_unlock(philo->right_mutex);
	return (1);
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

int	init_philos(t_philo *ph, t_info *info)
{
	if (init_mutex(ph, info))
		return (1);
	if (init_forks(ph, info))
		return (1);
	return (0);
}

int	init_mutex(t_philo *ph, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->no_of_philos)
	{
		if (pthread_mutex_init(&info->mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	pthread_mutex_init(&info->pd_mutex,NULL);
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