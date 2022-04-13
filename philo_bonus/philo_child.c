/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:16:04 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/13 12:46:51 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_check_dead(t_args *arg)
{
	if (ft_get_time() - arg->time_left >= arg->time_die)
	{
		ft_write_sms(arg, "DIED");
		sem_post(arg->sem_die);
		sem_wait(arg->sem_write);
		free(arg->pid);
		exit (1);
	}
}

void	ft_meal_check(t_args *arg, int *meal)
{
	if (*meal == arg->must_eat - 1)
	{
		free(arg->pid);
		exit (0);
	}
	else if (*meal < arg->must_eat)
		*meal += 1;
}

void	ft_child_set(t_args *arg)
{
	int	meal;

	meal = 0;
	while (1)
	{
		ft_check_dead(arg);
		if (arg->id_ph == arg->nbr_philo && arg->nbr_philo != 1)
			sem_wait(arg->sem_odd);
		sem_wait(arg->sem_fork);
		ft_write_sms(arg, "is taking the left fork");
		sem_post(arg->sem_odd);
// !!!!!!!!!
		if ((ft_get_time() - arg->time_left) + arg->time_eat >= arg->time_die && arg->nbr_philo % 2 == 1)
			ft_usleep(arg,
				(ft_get_time() - arg->time_left) + arg->time_eat + 1);
// Problema con 4 410 200 200: blocca perché non sa che possono salvarsi
		if (arg->nbr_philo == 1)
			ft_usleep(arg, arg->time_die + 1);
		sem_wait(arg->sem_fork);
		ft_check_dead(arg);
		ft_write_sms(arg, "is taking the right fork");
		arg->time_left = ft_get_time();
		ft_write_sms(arg, "is eating");
		ft_usleep(arg, arg->time_eat);
		sem_post(arg->sem_fork);
		sem_post(arg->sem_fork);
		ft_meal_check(arg, &meal);
		ft_check_dead(arg);
		ft_write_sms(arg, "is sleeping");
		ft_usleep(arg, arg->time_sleep);
		ft_check_dead(arg);
		ft_write_sms(arg, "is thinking");
	}
}

void	ft_process_init(t_args *arg)
{
	int		i;

	i = 0;
	arg->pid = (int *) malloc (sizeof(int) * arg->nbr_philo);
	if (!arg->pid)
		exit(1);
	while (i < arg->nbr_philo)
	{
		if (i == 0 || arg->pid[i - 1] != 0)
		{
			arg->pid[i] = fork();
			if (arg->pid[i] == 0)
			{
				arg->id_ph = i + 1;
				ft_child_set(arg);
			}
		}
		i++;
	}
}
