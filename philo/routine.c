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

void	*ft_philo_is_dying(void *list)
{
	pthread_mutex_lock(&((t_list *)list)->arg->mutex_die);
	ft_write_sms((t_list *)list, "DIED");
	((t_list *)list)->arg->must_eat = -1;
	pthread_mutex_unlock(&((t_list *)list)->arg->mutex_die);
	return (0);
}

void	ft_philo_is_eating(void *list, t_list **tmp, int *i)
{
	((t_list *)list)->fork = 0;
	(*tmp)->fork = 0;
	ft_write_sms((t_list *)list, "is taking the left fork");
	ft_write_sms((t_list *)list, "is taking the right fork");
	((t_list *)list)->die = ft_get_time();
	ft_write_sms((t_list *)list, "is eating");
	ft_usleep(list, ((t_list *)list)->arg->time_eat);
	((t_list *)list)->fork = 1;
	(*tmp)->fork = 1;
	*i = 1;
}

int	ft_sleep_and_think(void *list, int i)
{
	if (i == 1)
	{
		ft_write_sms((t_list *)list, "is sleeping");
		if (ft_usleep(list, ((t_list *)list)->arg->time_sleep) == 0)
			return (1);
		ft_write_sms((t_list *)list, "is thinking");
	}
	return (0);
}

void	*ft_routine(void *list)
{
	t_list	**tmp;
	int		i;

	tmp = &((t_list *)list)->next;
	while (((t_list *)list)->arg->must_eat != -1)
	{
		i = 0;
		if (ft_get_time() - ((t_list *)list)->die
			>= ((t_list *)list)->arg->time_die)
			return (ft_philo_is_dying(list));
		pthread_mutex_lock(&((t_list *)list)->mutex);
		if (((t_list *)list)->arg->nbr_philo == 1)
		{
			ft_write_sms((t_list *)list, "is taking the left fork");
			ft_usleep(list, ((t_list *)list)->arg->time_die);
			ft_philo_is_dying(list);
			return (0);
		}
		pthread_mutex_lock(&(*tmp)->mutex);
		if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
			ft_philo_is_eating(list, tmp, &i);
		pthread_mutex_unlock(&((t_list *)list)->mutex);
		pthread_mutex_unlock(&(*tmp)->mutex);
		if (((t_list *)list)->eat > 1 && i == 1)
			((t_list *)list)->eat -= 1;
		else if (((t_list *)list)->eat - 1 == 0 && i == 1)
			return (0);
		if (ft_sleep_and_think(list, i) == 1)
			return (0);
	}
	return (0);
}
