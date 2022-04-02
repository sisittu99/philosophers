/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:18:48 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/02 11:26:42 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// * STRUCT DATA * //

typedef struct s_args
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	pthread_t		*ph;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_write;
	int				start_time;
}				t_args;

// * LIST * //

typedef struct s_list
{
	t_args			*arg;
	int				fork;
	int				id_ph;
	int				eat;
	int				die;
	struct s_list	*next;
}				t_list;

// * UTILS * //

int		ft_atoi(const char *str);
t_list	*ft_lstnew(t_args *arg, int i);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_delete(t_list **list);

// * TIME * //

int		get_time(void);
void	ft_usleep(long int time_in_ms);

// * CHECKERS * //

int		ft_nbr_eat(t_list *list);
int		ft_time_die(t_list *list);

#endif
