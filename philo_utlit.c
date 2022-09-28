#include "philo.h"

long    get_time()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return(current_time.tv_sec * 1000 + (long)(current_time.tv_usec / 1000));
} 

void    ag_usleep(long c, t_philo *ph)
{
    long start;

    start = get_time();
    while (1)
    {
        if (ph->general_info->death_flag != 1)
            is_alive(ph);
        else
            break;
        usleep(500);
        if (get_time() - start >= c)
            break;
    }
}

void    print_status(t_philo *ph, char c)
{
    pthread_mutex_lock(&ph->general_info->pd_mutex);
    if (ph->general_info->death_flag != 1)
    {
         if (c == 'f')
            printf("%ld %d has taken a fork\n",get_time() - ph->general_info->start_time,ph->philo_id);
        else if (c == 'e')
            printf("%ld %d  is eating\n",get_time() - ph->general_info->start_time,ph->philo_id);
        else if (c == 's')
            printf("%ld %d  is sleeping\n",get_time() - ph->general_info->start_time,ph->philo_id);
        else if (c == 't')
            printf("%ld %d  is thinking\n",get_time() - ph->general_info->start_time,ph->philo_id);
        else if (c == 'd')
            printf("%ld %d  died\n",get_time() - ph->general_info->start_time,ph->philo_id);
   }
    pthread_mutex_unlock(&ph->general_info->pd_mutex);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	while (i < count * size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}