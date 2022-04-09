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

void	*ft_philo_is_dying(void *list, t_list **tmp)
{
	ft_write_sms((t_list *)list, "DIED");
	((t_list *)list)->arg->must_eat = -1;
	pthread_mutex_unlock(&((t_list *)list)->mutex);
	pthread_mutex_unlock(&(*tmp)->mutex);
	return (0);
}

void	ft_philo_is_eating(void *list, t_list **tmp, int *i)
{
	ft_write_sms((t_list *)list, "is taking the left fork");
	ft_write_sms((t_list *)list, "is taking the right fork");
	((t_list *)list)->fork = 0;
	(*tmp)->fork = 0;
	((t_list *)list)->die = ft_get_time();
	ft_write_sms((t_list *)list, "is eating");
	ft_usleep(((t_list *)list)->arg->time_eat);
	((t_list *)list)->fork = 1;
	(*tmp)->fork = 1;
	*i = 1;
}

void	ft_sleep_and_think(void *list, int i)
{
	if (i == 1)
	{
		ft_write_sms((t_list *)list, "is sleeping");
		ft_usleep(((t_list *)list)->arg->time_sleep);
	}
	ft_write_sms((t_list *)list, "is thinking");
}

void	*ft_routine(void *list)
{
	t_list	**tmp;
	int		i;

	tmp = &((t_list *)list)->next;
	while (((t_list *)list)->arg->must_eat != -1)
	{
		i = 0;
		pthread_mutex_lock(&((t_list *)list)->mutex);
		pthread_mutex_lock(&(*tmp)->mutex);
		if (ft_get_time() - ((t_list *)list)->die
			>= ((t_list *)list)->arg->time_die)
			return (ft_philo_is_dying(list, tmp));
		else if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
			ft_philo_is_eating(list, tmp, &i);
		pthread_mutex_unlock(&((t_list *)list)->mutex);
		pthread_mutex_unlock(&(*tmp)->mutex);
		if (((t_list *)list)->eat > 1)
			((t_list *)list)->eat -= 1;
		else if (((t_list *)list)->eat - 1 == 0)
			return (0);
		ft_sleep_and_think(list, i);
	}
	return (0);
}
