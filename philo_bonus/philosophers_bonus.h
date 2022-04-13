/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:33:27 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/13 19:36:38 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

// * STRUCT DATA * //

typedef struct s_args
{
	int		*pid;
	int		id_ph;
	int		nbr_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	int		start_time;
	int		time_left;
	sem_t	*sem_die;
	sem_t	*sem_write;
	sem_t	*sem_fork;
	sem_t	*sem_odd;
}				t_args;

// * PROCESSES UTILS * //

void	ft_kill_child(t_args *arg, int def);
void	ft_sem_close(t_args *arg, int def);
void	ft_check_dead(t_args *arg);
void	ft_meal_check(t_args *arg);
void	ft_child_set(t_args *arg);

// * UTILS * //

void	ft_write_sms(t_args *arg, char *str);
int		ft_define_args(int argc, char **argv, t_args *arg);
void	ft_process_init(t_args *arg);
int		ft_atoi(const char *str);

// * TIME UTILS * //

int		ft_get_time(void);
void	ft_usleep(t_args *arg, int sleep);

#endif
