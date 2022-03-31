/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:03:33 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/31 12:08:24 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		free(*list);
		*list = tmp;
	}
}

// void	ft_lstdelone(t_list *lst, void (*del)(t_arg *))
// {
// 	t_list	*tmp;

// 	tmp = lst;
// 	if (lst != NULL)
// 	{
// 		lst = tmp->next;
// 		del(&tmp->arg);
// 		free(tmp);
// 	}
// }

// void	ft_lstclear(t_list **lst, void (*del)(t_arg *))
// {
// 	t_list	*tmp;

// 	if (*lst == NULL)
// 		return ;
// 	while (*lst != NULL)
// 	{
// 		tmp = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = tmp;
// 	}
// }
