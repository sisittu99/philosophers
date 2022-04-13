/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:12:57 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/13 18:29:31 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_get_time(void)
{
	static struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * (u_int64_t)1000) + (tm.tv_usec / 1000));
}

void	ft_usleep(t_args *arg, int sleep)
{
	long int	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < sleep)
	{
		ft_check_dead(arg);
		usleep((sleep % 100) + 1);
	}
}
