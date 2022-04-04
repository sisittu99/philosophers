/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:24:20 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/04 11:22:25 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	define_args(int argc, char **argv, t_args *arg)
{
	(void)argc;
	arg->nbr_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->start_time = get_time();
	if (argc == 6)
		arg->must_eat = ft_atoi(argv[5]);
	else
		arg->must_eat = 0;
}

void	write_sms(t_list *list, char *str)
{
	pthread_mutex_lock(&list->mutex_write);
	printf("%d ms %d %s\n", get_time() - list->arg->start_time,
		list->id_ph, str);
	if (str[0] != 'D')
		pthread_mutex_unlock(&list->mutex_write);
}

void	*routine(void *list)
{
	t_list	**tmp;
	int		i;

	tmp = &((t_list *)list)->next;
	while (1)
	{
		i = 0;

		pthread_mutex_lock(&((t_list *)list)->mutex);
		pthread_mutex_lock(&(*tmp)->mutex);
		if (get_time() - ((t_list *)list)->die >= ((t_list *)list)->arg->time_die)
		{
			printf("\n| %d | %d |\n", ((t_list *)list)->id_ph, (get_time() - ((t_list *)list)->die));
			write_sms((t_list *)list, "DIED");
			exit (0);
		}
		if (((t_list *)list)->fork == 1 && (*tmp)->fork == 1)
		{
			printf("\nPRE EAT -> | %d | %d |\n", ((t_list *)list)->id_ph, (get_time() - ((t_list *)list)->die));
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
			printf("\nAFTER EAT -> | %d | %d |\n", ((t_list *)list)->id_ph, (get_time() - ((t_list *)list)->die));
			// pthread_mutex_unlock(&((t_list *)list)->mutex_eat);
		}
		pthread_mutex_unlock(&((t_list *)list)->mutex);
		pthread_mutex_unlock(&(*tmp)->mutex);

		if (i == 1)
		{
			write_sms((t_list *)list, "is sleeping");
			ft_usleep(((t_list *)list)->arg->time_sleep);
		}
		// else
		// 	write_sms((t_list *)list, "is thinking");
	}
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
		new = ft_lstnew(arg, i);
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

	list = NULL;
	ft_ph_init(&list, arg);
	i = 0;
	pthread_mutex_init(&list->mutex, NULL);
	// pthread_mutex_init(&list->arg->mutex, NULL);
	pthread_mutex_init(&list->mutex_eat, NULL);
	pthread_mutex_init(&list->mutex_write, NULL);
	while (i < arg->nbr_philo)
	{
		if (pthread_create(&arg->ph[i], NULL, routine, list) != 0)
			return (printf("Error: didn't create\n"));
		if (i != arg->nbr_philo - 1)
			list = list->next;
		i++;
	}
	i = -1;
	while (++i < arg->nbr_philo)
		if (pthread_join(arg->ph[i], NULL) != 0)
			return (printf("Error: didn't join\n"));
	pthread_mutex_destroy(&list->mutex);
	// pthread_mutex_destroy(&list->arg->mutex);
	pthread_mutex_destroy(&list->mutex_eat);
	pthread_mutex_destroy(&list->mutex_write);
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
	define_args(argc, argv, &arg);
	arg.ph = (pthread_t *)malloc(sizeof(pthread_t) * arg.nbr_philo);
	if (!arg.ph)
		return (1);
	if (ft_main2(&arg) != 0)
		return (1);
	return (0);
}
