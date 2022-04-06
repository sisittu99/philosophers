/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:18 by fdrudi            #+#    #+#             */
/*   Updated: 2022/04/06 18:40:37 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args	arg;

	if (argc != 6 && argc != 5)
	{
		write(2, "Invalid arguments. Exit", 24);
		exit(1);
	}
	define_args(argc, argv, &arg);
	while (wait(NULL) != -1);
	sem_close(arg.sem);
	return (0);
}
