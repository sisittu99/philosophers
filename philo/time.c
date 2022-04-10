/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:12:57 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/10 16:56:29 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_get_time(void)
{
	static struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * (u_int64_t)1000) + (tm.tv_usec / 1000));
}

int	ft_usleep(void *list, int sleep)
{
	long int	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < sleep)
	{
		if ((ft_get_time() - start_time) >= ((t_list *)list)->arg->time_die)
			return ((int) ft_philo_is_dying(list));
		if (((t_list *)list)->arg->must_eat == -1)
			return (0);
		usleep((sleep % 100) + 1);
	}
	return (1);
}
