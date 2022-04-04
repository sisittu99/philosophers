/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:34:24 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/04 19:34:24 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void	*routine(void *list)
{
	t_list	**tmp;
	int		i;

	tmp = &((t_list *)list)->next;
	while (((t_list *)list)->arg->must_eat != -1)
	{
		i = 0;

		pthread_mutex_lock(&((t_list *)list)->mutex);
		pthread_mutex_lock(&(*tmp)->mutex);
		if (get_time() - ((t_list *)list)->die >= ((t_list *)list)->arg->time_die)
		{
			write_sms((t_list *)list, "DIED");
			((t_list *)list)->arg->must_eat = -1;
			pthread_mutex_unlock(&((t_list *)list)->mutex);
			pthread_mutex_unlock(&(*tmp)->mutex);
			return (0);
		}
		else if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
		{
			write_sms((t_list *)list, "is taking the left fork");
			write_sms((t_list *)list, "is taking the right fork");
			((t_list *)list)->fork = 0;
			(*tmp)->fork = 0;
			// pthread_mutex_lock(&((t_list *)list)->arg->mutex_eat);
			((t_list *)list)->die = get_time();
			write_sms((t_list *)list, "is eating");
			ft_usleep(((t_list *)list)->arg->time_eat);
			((t_list *)list)->fork = 1;
			(*tmp)->fork = 1;
			i = 1;
			// pthread_mutex_unlock(&((t_list *)list)->mutex_eat);
		}
		pthread_mutex_unlock(&((t_list *)list)->mutex);
		pthread_mutex_unlock(&(*tmp)->mutex);
		if (((t_list *)list)->eat > 1)
			((t_list *)list)->eat -= 1;
		else if (((t_list *)list)->eat - 1 == 0)
			return (0);
		if (i == 1)
		{
			write_sms((t_list *)list, "is sleeping");
			ft_usleep(((t_list *)list)->arg->time_sleep);
		}
			write_sms((t_list *)list, "is thinking");
	}
	return (0);
}

