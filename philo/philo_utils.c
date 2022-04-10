/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:27:31 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/10 12:28:37 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_write_sms(t_list *list, char *str)
{
	pthread_mutex_lock(&list->arg->mutex_write);
	if (list->arg->must_eat == -1)
	{
		pthread_mutex_unlock(&list->arg->mutex_write);
		return ;
	}
	printf("%d ms %d %s\n", ft_get_time() - list->arg->start_time,
		list->id_ph, str);
	pthread_mutex_unlock(&list->arg->mutex_write);
}

int	ft_define_args(int argc, char **argv, t_args *arg)
{
	(void)argc;
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->start_time = ft_get_time();
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = 0;
	if (arg->nbr_philo <= 0 || arg->time_die <= 0 || arg->time_eat <= 0
		|| arg->time_sleep <= 0 || arg->must_eat < 0)
		return (printf("Invalid arguments. Exit\n"));
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
	if (j >= 11)
		return (-1);
	return (y);
}
