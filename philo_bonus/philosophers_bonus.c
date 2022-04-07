/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/07 17:54:35 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args	arg;
	int		stat;
	int		i;

	i = 0;
	stat = 0;
	if (argc != 6 && argc != 5)
	{
		write(2, "Invalid arguments. Exit", 24);
		exit(1);
	}
	define_args(argc, argv, &arg);
	while (i < arg.nbr_philo && arg.must_eat > 0)
	{
		waitpid(-1, &stat, 0);
		if (!(WIFEXITED(stat)))
		{
			i = 0;
			while (i < arg.nbr_philo)
			{
				kill(arg.pid[i], SIGKILL);
				i++;
			}
			sem_close(arg.sem_die);
			sem_close(arg.sem_fork);
			sem_close(arg.sem_write);
			return (0);
		}
		i++;
	}
	if (arg.must_eat <= 0)
	{
		sem_wait(arg.sem_die);
		while (i < arg.nbr_philo)
		{
			kill(arg.pid[i], SIGKILL);
			i++;
		}
	}
	sem_close(arg.sem_die);
	sem_close(arg.sem_fork);
	sem_close(arg.sem_write);
	return (0);
}
