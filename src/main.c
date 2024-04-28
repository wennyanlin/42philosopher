/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/04/28 22:37:46 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

t_rule	*get_all_philos_rules(t_rule rule, pthread_mutex_t	mutex)
{
	int		i;
	t_rule	*all_rules;

	i = -1;
	all_rules = malloc(sizeof(t_rule) * rule.n_philo);
	while (++i < rule.n_philo)
		all_rules[i] = struct_copy(rule, i + 1, &mutex);
	return (all_rules);
}

int	main(int argc, char **argv)
{
	t_rule	rule;
	t_rule	*all_rules;
	pthread_mutex_t	mutex;

	if (argc == 5 || argc == 6)
	{
		pthread_mutex_init(&mutex, NULL);
		if (validate_args(argc, argv) == FALSE)
			return (write_error(), EXIT_FAILURE);
		get_dining_rules(argc, argv, &rule);
		all_rules = get_all_philos_rules(rule, mutex);
		start_dining(all_rules, rule.n_philo);
		pthread_mutex_destroy(&mutex);
	}
	else
		write_error();
	return (0);
}
