/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/04/25 11:58:50 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc == 5 || argc == 6)
	{
		if (validate_args(argc, argv) == FALSE)
			return (write_error(), EXIT_FAILURE);
		get_dining_rules(argc, argv, &rule);
		// start_dining();
	}
	else
		write_error();
	return (0);
}
