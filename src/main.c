/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/04/24 23:42:26 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

int	main(int argc, char **argv)
{
	// int	n_philo;
	// int	t_die;
	// int	t_eat;
	// int	t_sleep;
	
	if (argc == 5)
	{
		if (validate_args(argc, argv) == FALSE)
			return (write_error(), 1);
	}
	else
		write_error();
	return (0);
}
