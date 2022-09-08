#include "philo.h"

long	get_time()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return(current_time.tv_sec * 1000 + (long)(current_time.tv_usec / 1000));
}

int    ag_usleep(long c, t_philo *ph)
{
    long start;

    start = get_time();
    while (1)
    {
        if (!is_alive(ph))
        {
            ph->general_info->death_flag = 1;
			printf("no philo %d philo is dead\n",ph->philo_id);
			return (0);
        }
        usleep(500);
        if (get_time() - start >= c)
            return (1) ;
    }
}