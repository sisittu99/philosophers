/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_eat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:20:02 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/02 12:05:39 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_max_nbr(t_list *list, int n)
{
	t_list	*tmp;
	int		max;

	tmp = list->next;
	max = list->eat;
	while (tmp->id_ph != n)
	{
		if (tmp->eat > max)
			max = tmp->eat;
		tmp = tmp->next;
	}
	return (max);
}

int	ft_min_nbr(t_list *list, int n)
{
	t_list	*tmp;
	int		min;

	tmp = list->next;
	min = list->eat;
	while (tmp->id_ph != n)
	{
		if (tmp->eat < min)
			min = tmp->eat;
		tmp = tmp->next;
	}
	return (min);
}

int	ft_max_nbr_die(t_list *list, int n)
{
	t_list	*tmp;
	int		max;

	tmp = list->next;
	max = list->die;
	while (tmp->id_ph != n)
	{
		if (tmp->die > max)
			max = tmp->die;
		tmp = tmp->next;
	}
	return (max);
}

int	ft_min_nbr_die(t_list *list, int n)
{
	t_list	*tmp;
	int		min;

	tmp = list->next;
	min = list->die;
	while (tmp->id_ph != n)
	{
		if (tmp->die < min)
			min = tmp->die;
		tmp = tmp->next;
	}
	return (min);
}

int	ft_nbr_eat(t_list *list)
{
	t_list	*tmp;
	int		n;

	tmp = list->next;
	n = list->id_ph;
	if (list->die == ft_max_nbr_die(list, n))
		return (0);
	else if (list->die > ft_min_nbr_die(list, n) && list->eat == ft_min_nbr(list, n))
		return (0);
	else if (list->die > ft_min_nbr_die(list, n) && list->eat < ft_max_nbr(list, n))
		return (0);
	else if (list->die == ft_min_nbr_die(list, n) && list->eat < ft_max_nbr(list, n))
		return (0);
	else if (list->die > ft_min_nbr_die(list, n) && list->eat == ft_max_nbr(list, n))
		return (0);
	else if (list->die == ft_min_nbr_die(list, n) && list->eat == ft_max_nbr(list, n))
		return (0);
	// tmp = tmp->next;
	// while (tmp->id_ph != n && list->eat == tmp->eat)
	// {
	// 	tmp = tmp->next;
	// 	if (tmp->id_ph == n)
	// 		return (0);
	// }
	return (1);
}
