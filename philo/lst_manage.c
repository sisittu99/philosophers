/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:03:33 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/05 01:24:29 by mcerchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_list	*ft_lstnew(t_args *arg, int i)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->arg = (t_args *) malloc (sizeof(t_args) * 1);
	if (!new->arg)
		return (NULL);
	new->arg = arg;
	new->id_ph = i + 1;
	new->eat = arg->must_eat;
	new->die = get_time();
	new->fork = 1;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst != NULL)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
	else
		(*lst) = new;
}

void	ft_lst_delete(t_list **list)
{
	t_list	*tmp;
	int		i;

	if (*list == NULL)
		return ;
	tmp = *list;
	i = (*list)->arg->nbr_philo;
	while (i--)
	{
		tmp = (*list)->next;
		free((*list)->arg);
		free(*list);
		*list = tmp;
	}
}
