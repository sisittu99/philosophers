/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:33:16 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/05 16:35:15 by fdrudi           ###   ########.fr       */
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
	int				start_time;
	pthread_mutex_t	mutex_write;
}				t_args;

// * LIST * //

typedef struct s_list
{
	t_args			*arg;
	int				fork;
	int				id_ph;
	int				die;
	int				eat;
	pthread_mutex_t	mutex;
	struct s_list	*next;
}				t_list;

// * ROUTINE * //

void	*routine(void *list);
void	write_sms(t_list *list, char *str);

// * UTILS * //

int		define_args(int argc, char **argv, t_args *arg);
int		ft_atoi(const char *str);

// * LIST UTILS *//

int		ft_ph_init(t_list **list, t_args *arg);
t_list	*ft_lstnew(t_args *arg, int i);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_delete(t_list **list);

// * TIME * //

int		get_time(void);
void	ft_usleep(long int time_in_ms);

#endif
