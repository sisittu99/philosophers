/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/05 15:46:596 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_main3(t_list *list, t_args *arg)
{
	int			i;
	int			*r;
	pthread_t	*ph;

	ph = (pthread_t *)malloc(sizeof(pthread_t) * arg->nbr_philo);
	if (!ph)
		return (1);
	i = 0;
	while (i < arg->nbr_philo)
	{
		if (pthread_create(&ph[i], NULL, routine, list) != 0)
			return (printf("Error: didn't create\n"));
		if (i != arg->nbr_philo - 1)
			list = list->next;
		i++;
	}
	r = (int *) malloc (sizeof(int) * i);
	if (!r)
		return (1);
	while (i--)
		if (pthread_join(ph[i], (void *)&(r[i])) != 0)
			return (printf("Error: %d didn't join\n", i + 1));
	i = 0;
	while (i < arg->nbr_philo)
	{
		if (r[i] == 1)
		{
			free(ph);
			free(r);
			return (1);
		}
		i++;
	}
	free(r);
	free(ph);
	return (0);
}

int	ft_main2(t_args *arg)
{
	t_list	*list;
	int		i;

	i = 0;
	list = NULL;
	ft_ph_init(&list, arg);
	pthread_mutex_init(&list->mutex, NULL);
	pthread_mutex_init(&list->arg->mutex_write, NULL);
	i = ft_main3(list, arg);
	pthread_mutex_destroy(&list->mutex);
	pthread_mutex_destroy(&list->arg->mutex_write);
	ft_lst_delete(&list);
	if (i != 0)
		return (1);
	return (0);
}

//things to free:	1) arg.ph
//					2) every list node
//					3) every arg node inside list


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
	if (ft_main2(&arg) != 0)
		return (1);
	return (0);
}
