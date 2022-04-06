/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:32:27 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/06 17:51:1 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	define_args(int argc, char **argv, t_args *arg)
{
	(void)argc;
	sem_unlink("sem");
	arg->sem = sem_open("sem", O_CREAT, 0644, 1);
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->start_time = get_time();
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = 0;
	if (arg->nbr_philo <= 0 || arg->time_die <= 0 || arg->time_eat <= 0
		|| arg->time_sleep <= 0 || arg->must_eat < 0)
	{
		printf("Invalid arguments. Exit\n");
		exit(1);
	}
	ft_process_init(arg);
	return (0);
}

void	ft_process_init(t_args *arg)
{
	int		i;
	int		sem_val;

	i = -1;
	arg->pid = (int *) malloc (sizeof(int) * arg->nbr_philo);
	if (!arg->pid)
		exit(1);
	while (i < arg->nbr_philo - 1)
	{
		if (i < 0 || arg->pid[i - 1] != 0)
		{
			arg->pid[i] = fork();
			if (arg->pid[i] == 0)
			{
				sem_post(arg->sem);
				sem_getvalue(arg->sem, &sem_val);
				printf("%d° Child Process Created with Sem: %d\n", i + 2, sem_val);
			}
			else
			{
				sem_getvalue(arg->sem, &sem_val);
				printf("Parent Sem: %d\n", sem_val);
			}
		}
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c > 57 || c < 48)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	y;
	int	j;

	y = 0;
	j = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43)
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		y = (y * 10) + ((*str - 48) % 10);
		str++;
		j++;
	}
	if (j >= 10)
		return (-1);
	return (y);
}
