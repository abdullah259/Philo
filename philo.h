#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info{
	int	no_of_philos;
	int	*forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	no_of_times_eat;
	int	death_flag;
	long start_time;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	pd_mutex;
}t_info;

typedef struct s_philo{
	long			start_eat;
	int				philo_id;
	t_info			*general_info;
	int				*right_fork;
	int				*left_fork;
	pthread_mutex_t	*right_mutex;
	pthread_mutex_t	*left_mutex;
}t_philo;

int     drop_forks(t_philo *philo);
int     take_forks(t_philo *philo);
int     init_forks(t_philo *ph, t_info *info);
int     init_philos(t_philo *ph, t_info *info);
int     init_mutex(t_philo *ph, t_info *info);
long 	get_time();
void    ag_usleep(long c, t_philo *ph);
void	is_alive(t_philo *ph);
void    print_status(t_philo *ph, char c);
int		ft_atoi(char *str);
int		parse_input(int ac, char **av, t_info *info);
void	*ft_calloc(size_t count, size_t size);
#endif