#include "philo.h"


int	check_after_num(char c, char c1, char c2)
{
	if ((c == '-' || c == '+') && (c1 >= '0' && c1 <= '9') &&
		(c2 == '-' || c2 == '+'))
	{
		printf("you have not number bacuse there is not exist number before - or + then number\n");
		// exit(1);
		return (0);
	}
	if ((c == '-' || c == '+') && (c1 == '\0'|| c1 == ' ' || c1 == '\t'))
	{
		printf("ther is single char no numbers\n");
		return (0);
	}
	if (c1 == '-' || c1 == '+')
	{
		printf("there is muluplie char\n");
		return (0);;
	}
	return(1);
}

int	check_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '-' || argv[i][j] == '+')
			{
				if (check_after_num(argv[i][j], argv[i][j + 1], argv[i][j + 2]) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int check_after_convert(t_info *info, int ac)
{
	if (ac == 5)
	{
		if (info->no_of_philos < 0 || info->time_to_die < 0 || info->time_to_eat < 0 || info->time_to_sleep < 0)
			return (1);
		if (info->no_of_philos == 0 || info->time_to_die == 0 || info->time_to_eat == 0 || info->time_to_sleep == 0)
			return (1);
	}
	else if (ac == 6)
	{
		if (info->no_of_philos < 0 || info->time_to_die < 0 || info->time_to_eat < 0 || info->time_to_sleep < 0 || info->no_of_times_eat < 0)
			return (1);
		if (info->no_of_philos == 0 || info->time_to_die == 0 || info->time_to_eat == 0 || info->time_to_sleep == 0 || info->no_of_times_eat == 0)
			return (1);
	}
	return (0);
}

int parse_input(int ac, char **av, t_info *info)
{
	if (check_valid(av))
	{
		info->no_of_philos = ft_atoi(av[1]);
		if (info->no_of_philos == -1 || info->no_of_philos == 0)
			return (1);
		info->time_to_die = ft_atoi(av[2]);
		if (info->no_of_philos == -1 || info->no_of_philos == 0)
			return (1);
		info->time_to_eat = ft_atoi(av[3]);
		if (info->no_of_philos == -1  || info->no_of_philos == 0)
			return (1);
		info->time_to_sleep = ft_atoi(av[4]);
		if (info->no_of_philos == -1 || info->no_of_philos == 0)
			return (1);
		if(ac == 6)
		{
			info->no_of_times_eat = ft_atoi(av[5]);
			if (info->no_of_philos == -1 || info->no_of_philos == 0)
				return (1);
		}
		if (check_after_convert(info, ac) == 1)
			return (1);
		return (0);
	}
	return (1);
}