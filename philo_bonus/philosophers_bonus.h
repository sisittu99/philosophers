/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcerchi <mcerchi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:33:27 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/06 18:333:55 by mcerchi          ###   ########.fr       */
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

// * STRUCT DATA * //

typedef struct s_args
{
	int	*pid;
	int	nbr_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
	int	start_time;
	sem_t	*sem;
}				t_args;

// * UTILS * //

int		define_args(int argc, char **argv, t_args *arg);
void	ft_process_init(t_args *arg);
int		ft_atoi(const char *str);

// * TIME UTILS * //

int		get_time(void);
void	ft_usleep(long int time_in_ms);

#endif
