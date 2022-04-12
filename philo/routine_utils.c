/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:47:35 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/12 18:50:48 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_lonely_philo(void *list)
{
	pthread_mutex_lock(&((t_list *)list)->mutex);
	ft_write_sms((t_list *)list, "is taking the left fork");
	ft_usleep(list, ((t_list *)list)->arg->time_die);
	pthread_mutex_unlock(&((t_list *)list)->mutex);
	return (ft_philo_is_dying(list));
}

void	ft_check_id(void *list, t_list **tmp)
{
	if (((t_list *)list)->id_ph != ((t_list *)list)->arg->nbr_philo)
	{
		pthread_mutex_lock(&((t_list *)list)->mutex);
		((t_list *)list)->fork = 0;
		ft_write_sms((t_list *)list, "is taking the left fork");
		pthread_mutex_lock(&(*tmp)->mutex);
		(*tmp)->fork = 0;
		ft_write_sms((t_list *)list, "is taking the right fork");
	}
	else
	{
		pthread_mutex_lock(&(*tmp)->mutex);
		(*tmp)->fork = 0;
		ft_write_sms((t_list *)list, "is taking the right fork");
		pthread_mutex_lock(&((t_list *)list)->mutex);
		((t_list *)list)->fork = 0;
		ft_write_sms((t_list *)list, "is taking the left fork");
	}
}
