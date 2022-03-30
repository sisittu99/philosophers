/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/30 19:32:44 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	define_args(int argc, char **argv, t_args *arg)
{
	(void) argc;
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = 0;
}

void	*routine(void *arg)
{
	t_list	*tmp;

	tmp = (t_list *) arg;
	pthread_mutex_lock(&tmp->arg->mutex);
	usleep(100);
	printf("nbr Phil : %d\n", tmp->fork);
	printf("Hello World !\n");
	pthread_mutex_unlock(&tmp->arg->mutex);
	return (0);
}

int	ft_ph_init(t_list **list, t_args *arg)
{
	int		i;
	t_list	*new;
	t_list	*tmp;

	i = -1;
	while (++i < arg->nbr_philo)
	{
		new = ft_lstnew(arg);
		ft_lstadd_back(list, new);
	}
	tmp = (*list);
	while ((*list)->next != NULL)
		*list = (*list)->next;
	(*list)->next = tmp;
	*list = (*list)->next;
	return (0);
}

int	ft_main2(t_args *arg)
{
	t_list	*list;
	int		i;

	ft_ph_init(&list, arg);
	i = -1;
	pthread_mutex_init(&list->arg->mutex, NULL);
	while (++i < arg->nbr_philo)
	{
		if (pthread_create(&arg->ph[i], NULL, &routine, list) != 0)
			return (printf("Error: didn't create\n"));
		if (i != arg->nbr_philo - 1)
			list = list->next;
	}
	i = -1;
	while (++i < arg->nbr_philo)
		if (pthread_join(arg->ph[i], NULL) != 0)
			return (printf("Error: didn't join\n"));
	pthread_mutex_destroy(&list->arg->mutex);
	// ft_lst_delete(&list);							FREE LISTA DA SISTEMARE
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		arg;
	int			i;

	if (argc != 6 && argc != 5)
	{
		write(2, "Invalid arguments. Exit", 24);
		return (1);
	}
	define_args(argc, argv, &arg);
	arg.ph = (pthread_t *) malloc (sizeof(pthread_t) * arg.nbr_philo);
	if (!arg.ph)
		return (1);
	i = -1;
	if (ft_main2(&arg) != 0)
		return (1);
	return (0);
}
