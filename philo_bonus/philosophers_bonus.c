/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/11 18:29:35 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sem_close(t_args *arg, int def)
{
	sem_close(arg->sem_die);
	sem_close(arg->sem_fork);
	sem_close(arg->sem_write);
	if (def == 1)
		free(arg->pid);
}

void	ft_kill_child(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->nbr_philo)
	{
		kill(arg->pid[i], SIGKILL);
		i++;
	}
	ft_sem_close(arg, -1);
}

int	main(int argc, char **argv)
{
	t_args	arg;
	int		stat;
	int		i;

	i = 0;
	stat = 0;
	if (argc != 6 && argc != 5)
		exit(write(2, "Invalid arguments. Exit", 24));
	ft_define_args(argc, argv, &arg);
	while (i < arg.nbr_philo)
	{
		if (arg.must_eat > 0)
		{
			printf("EXIT\n");								//SISTEMARE PER CASO 5 500 200 200
			waitpid(-1, &stat, 0);							//NON ESCE QUANDO DOVREBBE
			printf("EXIT 1\n");								//SE SI TOGLIE IL WHILE FUNZIONA MA
			if (!(WIFEXITED(stat)))							//POI ERRORE SU USCITA CORRETTA IN 5 800 200 200 7
			{
				printf("EXIT 2\n");
				ft_kill_child(&arg);
				return (0);
			}
		}
		i++;
	}
	if (arg.must_eat <= 0)
	{
		sem_wait(arg.sem_die);
		ft_kill_child(&arg);
	}
	ft_sem_close(&arg, 1);
	return (0);
}
