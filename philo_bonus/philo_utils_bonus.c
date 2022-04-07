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

void	write_sms(t_args *arg, char *str)
{
	sem_wait(arg->sem_write);
	printf("%d ms %d %s\n", get_time() - arg->start_time,
		arg->id_ph, str);
	sem_post(arg->sem_write);
}

void	ft_check_dead(t_args *arg)
{
	if (get_time() - arg->time_left >= arg->time_die)
	{
		write_sms(arg, "DIED");
		sem_post(arg->sem_die);
		sem_wait(arg->sem_write);
		exit(1);
	}
}

void	ft_meal_check(t_args *arg, int *meal)
{
	if (*meal == arg->must_eat)
		exit (0);
	else if (*meal < arg->must_eat)
		*meal += 1;
}

int	define_args(int argc, char **argv, t_args *arg)
{
	arg->id_ph = 0;
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->start_time = get_time();
	arg->time_left = arg->start_time;
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = -1;
	if (arg->nbr_philo <= 0 || arg->time_die <= 0 || arg->time_eat <= 0
		|| arg->time_sleep <= 0 || arg->must_eat < -1
		|| arg->time_eat >= arg->time_die)
	{
		printf("Invalid arguments. Exit\n");
		exit(1);
	}
	sem_unlink("sem_die");
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	arg->sem_die = sem_open("sem_die", O_CREAT, 0644, 0);
	arg->sem_fork = sem_open("sem_fork", O_CREAT, 0644, arg->nbr_philo);
	arg->sem_write = sem_open("sem_write", O_CREAT, 0644, 1);
	ft_process_init(arg);
	return (0);
}

void	ft_child_set(t_args *arg)
{
	int	meal;

	meal = 0;
	while (1)
	{
		ft_check_dead(arg);
		sem_wait(arg->sem_fork);
		write_sms(arg, "is taking the left fork");
		sem_wait(arg->sem_fork);
		write_sms(arg, "is taking the right fork");
		arg->time_left = get_time();
		write_sms(arg, "is eating");
		ft_usleep(arg->time_eat);
		sem_post(arg->sem_fork);
		sem_post(arg->sem_fork);
		ft_meal_check(arg, &meal);
		write_sms(arg, "is sleeping");
		ft_usleep(arg->time_sleep);
		ft_check_dead(arg);
		write_sms(arg, "is thinking");
	}
}

void	ft_process_init(t_args *arg)
{
	int		i;

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
				arg->id_ph = i + 2;
				ft_child_set(arg);
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
