/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:18:48 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/30 19:32:41 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_args
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	pthread_t		*ph;
	pthread_mutex_t	mutex;
}				t_args;

typedef struct s_list
{
	t_args			*arg;
	int				fork;
	struct s_list	*next;
}				t_list;

// * UTILS * //

int		ft_atoi(const char *str);
t_list	*ft_lstnew(t_args *arg);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_delete(t_list **list);
// void	ft_lstdelone(t_list *lst, void (*del)(int *));
// void	ft_lstclear(t_list **lst, void (*del)(int *));

#endif
