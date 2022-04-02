/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_die.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:23:57 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/02 11:45:20 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	ft_max_nbr_die(t_list *list, int n)
// {
// 	t_list	*tmp;
// 	int		max;

// 	tmp = list->next;
// 	max = list->die;
// 	while (tmp->id_ph != n)
// 	{
// 		if (tmp->die > max)
// 			max = tmp->die;
// 		tmp = tmp->next;
// 	}
// 	return (max);
// }

// int	ft_min_nbr_die(t_list *list, int n)
// {
// 	t_list	*tmp;
// 	int		min;

// 	tmp = list->next;
// 	min = list->die;
// 	while (tmp->id_ph != n)
// 	{
// 		if (tmp->die < min)
// 			min = tmp->die;
// 		tmp = tmp->next;
// 	}
// 	return (min);
// }

// int	ft_time_die(t_list *list)
// {
// 	t_list	*tmp;
// 	int		n;

// 	tmp = list->next;
// 	n = list->id_ph;
// 	if (list->die == ft_max_nbr_die(list, n))
// 		return (0);
// 	else if (list->die > ft_min_nbr_die(list, n))
// 		return (0);
// 	tmp = tmp->next;
// 	while (tmp->id_ph != n && list->die == tmp->die)
// 	{
// 		tmp = tmp->next;
// 		if (tmp->id_ph == n)
// 			return (0);
// 	}
// 	return (1);
// }
