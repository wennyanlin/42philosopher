/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/04/30 09:32:26 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

pthread_mutex_t	create_fork()
{
	pthread_mutex_t	fork;

	pthread_mutex_init(&fork, NULL);
	return (fork);
}

pthread_mutex_t *create_forks_array(int n_philos)
{
	pthread_mutex_t	*forks_array;
	int				i;

	forks_array = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks_array)
		return (NULL);
	i = -1;
	while (++i < n_philos)
		forks_array[i] = create_fork();
	return (forks_array);
}

t_rule	*get_all_philos_rules(t_rule rule)
{
	int		i;
	t_rule	*all_rules;
	pthread_mutex_t	*forks_array;

	i = -1;
	all_rules = malloc(sizeof(t_rule) * rule.n_philo);
	if (!all_rules)
		return (NULL);
	forks_array = create_forks_array(rule.n_philo);
	while (++i < rule.n_philo)
	{
		if (i == rule.n_philo - 1)
			all_rules[i] = struct_copy(rule, i + 1, &forks_array[i], &forks_array[0]);
		else
			all_rules[i] = struct_copy(rule, i + 1, &forks_array[i], &forks_array[i + 1]);
	}
	return (all_rules);
}

int	main(int argc, char **argv)
{
	t_rule	rule;
	t_rule	*all_rules;
	int		i;

	if (argc == 5 || argc == 6)
	{
		i = -1;
		if (validate_args(argc, argv) == FALSE)
			return (write_error(), EXIT_FAILURE);
		get_dining_rules(argc, argv, &rule);
		all_rules = get_all_philos_rules(rule);
		start_dining(all_rules, rule.n_philo);
		while (++i < rule.n_philo)
			pthread_mutex_destroy(all_rules[i].left_fork);
	}
	else
		write_error();
	return (0);
}
