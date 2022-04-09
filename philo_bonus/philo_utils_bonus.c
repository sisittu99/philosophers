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

void	ft_write_sms(t_args *arg, char *str)
{
	sem_wait(arg->sem_write);
	printf("%d ms %d %s\n", ft_get_time() - arg->start_time,
		arg->id_ph, str);
	sem_post(arg->sem_write);
}

int	ft_define_args(int argc, char **argv, t_args *arg)
{
	arg->id_ph = 0;
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->start_time = ft_get_time();
	arg->time_left = arg->start_time;
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = -1;
	if (arg->nbr_philo <= 0 || arg->time_die <= 0 || arg->time_eat <= 0
		|| arg->time_sleep <= 0 || arg->must_eat < -1
		|| arg->time_eat >= arg->time_die)
		exit(write(2, "Invalid arguments. Exit", 24));
	sem_unlink("sem_die");
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	arg->sem_die = sem_open("sem_die", O_CREAT, 0644, 0);
	arg->sem_fork = sem_open("sem_fork", O_CREAT, 0644, arg->nbr_philo);
	arg->sem_write = sem_open("sem_write", O_CREAT, 0644, 1);
	ft_process_init(arg);
	return (0);
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
