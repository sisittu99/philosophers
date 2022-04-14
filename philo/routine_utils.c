/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:47:35 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/14 18:20:27 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_lonely_philo(void *list)
{
	pthread_mutex_lock(&((t_list *)list)->mutex);
	ft_write_sms((t_list *)list, "is taking the left fork");
	ft_usleep(list, ((t_list *)list)->arg->time_die);
	pthread_mutex_unlock(&((t_list *)list)->mutex);
	ft_philo_is_dying(list);
	return (0);
}

int	ft_check_id2(void *list, t_list **tmp, int time)
{
	pthread_mutex_lock(&(*tmp)->mutex);
	ft_write_sms((t_list *)list, "is taking the right fork");
	(*tmp)->fork = 0;
	if (ft_philo_is_dying(list) == 1)
		return (1);
	if (time >= ((t_list *)list)->arg->time_die
		&& ((t_list *)list)->arg->nbr_philo % 2 == 1)
		if (ft_usleep(list, time + 1) == 0)
			return (1);
	pthread_mutex_lock(&((t_list *)list)->mutex);
	ft_write_sms((t_list *)list, "is taking the left fork");
	((t_list *)list)->fork = 0;
	return (0);
}

int	ft_check_id(void *list, t_list **tmp)
{
	int	time;

	time = ((ft_get_time() - ((t_list *)list)->die)
			+ ((t_list *)list)->arg->time_eat);
	while (1)
	{
		if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
		{
			((t_list *)list)->fork = 0;
			(*tmp)->fork = 0;
			break ;
		}
	}
	if (((t_list *)list)->id_ph != ((t_list *)list)->arg->nbr_philo)
	{
		pthread_mutex_lock(&((t_list *)list)->mutex);
		ft_write_sms((t_list *)list, "is taking the left fork");
		((t_list *)list)->fork = 0;
		if (ft_philo_is_dying(list) == 1)
			return (1);
		if (time >= ((t_list *)list)->arg->time_die
			&& ((t_list *)list)->arg->nbr_philo % 2 == 1)
			if (ft_usleep(list, time + 1) == 0)
				return (1);
		pthread_mutex_lock(&(*tmp)->mutex);
		ft_write_sms((t_list *)list, "is taking the right fork");
		(*tmp)->fork = 0;
	}
	else if (ft_check_id2(list, tmp, time) == 1)
		return (1);
	return (0);
}
