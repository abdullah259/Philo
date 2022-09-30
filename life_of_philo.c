#include "philo.h"

void	check_left(t_philo *philo)
{
	philo->left_fork->state = 1;
	philo->left_fork->last_used = philo->philo_id;
	philo->right_fork->last_used = philo->philo_id;
	print_status(philo, 'f');
	print_status(philo, 'f');
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_mutex);
	if (philo->right_fork->state == 0
		&& philo->right_fork->last_used != philo->philo_id)
	{
		philo->right_fork->state = 1;
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_lock(philo->left_mutex);
		if (philo->left_fork->state == 0
			&& philo->left_fork->last_used != philo->philo_id)
		{
			check_left(philo);
			pthread_mutex_unlock(philo->left_mutex);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(philo->left_mutex);
			pthread_mutex_lock(philo->right_mutex);
			philo->right_fork->state = 0;
		}
	}
	pthread_mutex_unlock(philo->right_mutex);
	return (1);
}

int	init_forks(t_philo *ph, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->no_of_philos)
	{
		ph[i].right_fork = &info->forks[i];
		if (i == 0)
			ph[i].left_fork = &info->forks[info->no_of_philos - 1];
		else
			ph[i].left_fork = &info->forks[i - 1];
		ph[i].right_fork->state = 0;
		ph[i].right_fork->last_used = -1;
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
	pthread_mutex_init(&info->pd_mutex, NULL);
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
