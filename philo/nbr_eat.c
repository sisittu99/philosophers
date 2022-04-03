/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_eat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:20:02 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/03 12:54:26 by fdrudi           ###   ########.fr       */
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
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_max_nbr_die(t_list *list, int n)
{
	t_list	*tmp;
	int		max;

	tmp = list->next;
	max = list->die;
	while (tmp->id_ph != n)
	{
		if (tmp->die >= max)
			return (1);
		tmp = tmp->next;
		if (tmp->id_ph == n)
			return (0);
	}
	return (0);
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

int	ft_dup_nbr_die(t_list *list, int n)
{
	t_list	*tmp;
	int		dup;

	tmp = list->next;
	dup = list->die;
	while (tmp->id_ph != n)
	{
		if (tmp->die == dup)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_dup_nbr(t_list *list, int n)
{
	t_list	*tmp;
	int		dup;

	tmp = list->next;
	dup = list->eat;
	while (tmp->id_ph != n)
	{
		if (tmp->eat == dup)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_equal(t_list *list, int n)
{
	t_list	*tmp;

	tmp = list->next;
	while (tmp->id_ph != n && list->eat == tmp->eat && list->die == tmp->die)
	{
		tmp = tmp->next;
		if (tmp->id_ph == n)
			return (0);
	}
	return (1);
}

int	ft_nbr_eat(t_list *list)
{
	t_list	*tmp;
	int		n;

	n = list->id_ph;
	tmp = list->next;
















	// if (ft_equal(list, n) == 0)
	// {
	// 	printf("| * Test 3 * |\n");
	// 	return (0);
	// }
	// if (ft_max_nbr_die(list, n) == 0)
	// {
	// 	printf("| * Test 1 * |\n");
	// 	count++;
	// }
	// if (ft_min_nbr(list, n) == 0)
	// {
	// 	printf("| * Test 2 * |\n");
	// 	count++;
	// }
	// if (count >= 1)
	// 	return (0);
	// return (1);
	// else if (list->die > ft_min_nbr_die(list, n))
	// {
	// 	printf("| * Test 3 * |\n");
	// 	if (list->eat < ft_max_nbr(list, n))
	// 		return (0);
	// 	else if (list->eat == ft_max_nbr(list, n))
	// 		return (0);
	// }
	// else if (list->die == ft_min_nbr_die(list, n))
	// {
	// 	printf("| * Test 4 * |\n");
	// 	if (list->eat < ft_max_nbr(list, n))
	// 		return (0);
	// 	else if (list->eat == ft_max_nbr(list, n))
	// 		return (0);
	// }
	// tmp = tmp->next;
	// while (tmp->id_ph != n && list->eat == tmp->eat)
	// {
	// 	tmp = tmp->next;
	// 	if (tmp->id_ph == n)
	// 		return (0);
	// }
	return ((0));
}
