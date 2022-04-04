/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/04 19:35:13 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_main3(t_list *list, t_args *arg)
{
	int		i;
	int		r;

	i = 0;
	while (i < arg->nbr_philo)
	{
		if (pthread_create(&arg->ph[i], NULL, routine, list) != 0)
			return (printf("Error: didn't create\n"));
		if (i != arg->nbr_philo - 1)
			list = list->next;
		i++;
	}
	r = 0;
	while (i--)
	{
		if (pthread_join(arg->ph[i], (void *)&r) != 0)
			return (printf("Error: %d didn't join\n", i + 1));
		if (r == 1)
			return (1);
	}
	return (0);
}

int	ft_main2(t_args *arg)
{
	t_list	*list;


	list = NULL;
	ft_ph_init(&list, arg);
	pthread_mutex_init(&list->mutex, NULL);
	pthread_mutex_init(&list->arg->mutex_write, NULL);
	if (ft_main3(list, arg) != 0)
		return (1);
	pthread_mutex_destroy(&list->mutex);
	pthread_mutex_destroy(&list->arg->mutex_write);
	// ft_lst_delete(&list);
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
