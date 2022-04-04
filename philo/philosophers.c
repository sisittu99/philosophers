/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/04 15:02:38 by fdrudi           ###   ########.fr       */
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
			return ((void*)1);
		}
		else if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
		{
			write_sms((t_list *)list, "is taking the left fork");
			write_sms((t_list *)list, "is taking the right fork");
			((t_list *)list)->fork = 0;
			(*tmp)->fork = 0;
			i = -1;
		}

		if (i == -1)
		{
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
	printf("PH : %d exit\n", ((t_list *)list)->id_ph);
	return (0);
}

int	ft_main2(t_args *arg)
{
	t_list	*list;
	int		i;
	int		r;

	list = NULL;
	ft_ph_init(&list, arg);
	i = 0;
	pthread_mutex_init(&list->mutex, NULL);
	// pthread_mutex_init(&list->mutex_eat, NULL);
	pthread_mutex_init(&list->arg->mutex_write, NULL);
	while (i < arg->nbr_philo)
	{
		if (pthread_create(&arg->ph[i], NULL, routine, list) != 0)
			return (printf("Error: didn't create\n"));
		if (i != arg->nbr_philo - 1)
			list = list->next;
		i++;
	}
	i = -1;
	r = 0;
	while (++i < arg->nbr_philo)
	{
		if (pthread_join(arg->ph[i], (void *)&r) != 0)
			return (printf("Error: %d didn't join\n", i + 1));
		if (r == 1)
			return (1);
	}

	pthread_mutex_destroy(&list->mutex);
	// pthread_mutex_destroy(&list->mutex_eat);
	pthread_mutex_destroy(&list->arg->mutex_write);
	ft_lst_delete(&list);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	arg;

	if (argc != 6 && argc != 5)
	{
		write(2, "Invalid arguments. Exit", 24);
		return (1);
	}
	if (define_args(argc, argv, &arg) != 0)
		return (1);
	arg.ph = (pthread_t *)malloc(sizeof(pthread_t) * arg.nbr_philo);
	if (!arg.ph)
		return (1);
	if (ft_main2(&arg) != 0)
		return (1);
	return (0);
}
