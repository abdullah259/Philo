#include "philo.h"

long	get_time()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return(current_time.tv_sec * 1000 + (long)(current_time.tv_usec / 1000));
}

void    ag_usleep(long c)
{
    long start;

    start = get_time();
    while (1)
    {
        usleep(150);
        if (get_time() - start >= c)
            break ;
    }
}