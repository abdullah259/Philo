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
