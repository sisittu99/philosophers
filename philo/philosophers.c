/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/13 18:17:07 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_pthread_create(pthread_t *ph, t_list *list, t_args *arg, int *r)
{
	int	i;

	i = 0;
	while (i < (arg)->nbr_philo)
	{
		if (pthread_create(&ph[i], NULL, ft_routine, list) != 0)
		{
			printf("Error: didn't create\n");
			return (-1);
		}
		if (i != arg->nbr_philo - 1)
			list = list->next;
		i++;
	}
	i = 0;
	while (i < (arg)->nbr_philo)
	{
		if (pthread_join(ph[i], (void *)&(r[i])) != 0)
		{
			printf("Error: %d didn't join\n", i + 1);
			return (-1);
		}
		i++;
	}
	return (i);
}

int	ft_main3(t_list *list, t_args *arg)
{
	int			i;
	int			*r;
	pthread_t	*ph;

	ph = (pthread_t *)malloc(sizeof(pthread_t) * arg->nbr_philo);
	r = (int *) malloc (sizeof(int) * arg->nbr_philo);
	if (!ph || !r)
		return (1);
	i = ft_pthread_create(ph, list, arg, r);
	if (i == -1)
		return (1);
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
	int		index;

	i = 0;
	index = 0;
	list = NULL;
	ft_ph_init(&list, arg);
	pthread_mutex_init(&list->mutex, NULL);
	pthread_mutex_init(&list->arg->mutex_write, NULL);
	pthread_mutex_init(&list->arg->mutex_die, NULL);
	i = ft_main3(list, arg);
	while (index < list->arg->nbr_philo)
	{
		pthread_mutex_destroy(&list->mutex);
		list = list->next;
		index++;
	}
	pthread_mutex_destroy(&list->arg->mutex_write);
	pthread_mutex_destroy(&list->arg->mutex_die);
	ft_lst_delete(&list);
	if (i != 0)
		return (1);
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
	if (ft_define_args(argc, argv, &arg) != 0)
		return (1);
	if (ft_main2(&arg) != 0)
		return (1);
	return (0);
}
