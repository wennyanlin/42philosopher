/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/05/18 12:50:33 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error(char *message)
{
	printf("Error: %s\n", message);
}

void	clean_up(t_data *data, pthread_mutex_t *all_forks)
{
	int		i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(data->all_philos[i].left_fork);
	pthread_mutex_destroy(&(data->mtx_end));
	pthread_mutex_destroy(&(data->mtx_info));
	pthread_mutex_destroy(&(data->mtx_printf));
	free(data->all_philos);
	free(all_forks);
}

void	dining_start(t_data *data)
{
	data->start_at = ft_time();
	if (data->num_philos == 1)
	{
		if (pthread_create(&data->all_philos[0].tid, NULL, &one_philo_routine,
				&data->all_philos[0]) != 0)
			printf("Failed to create thread.\n");
	}
	else
	{
		simulation(data);
		// pthread_mutex_unlock(&data->mtx_info);
		monitor(data);
	}
	return ;
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*all_forks;
	t_data			data;
	int				i;

	if (argc == 5 || argc == 6)
	{
		if (validate_dining_rules(argc, argv) == FALSE)
			return (write_error("dining rules are not valid."), EXIT_FAILURE);
		all_forks = dining_prepare(&data, argc, argv);
		dining_start(&data);
		i = -1;
		while (++i < data.num_philos)
			pthread_join(data.all_philos[i].tid, NULL);
		clean_up(&data, all_forks);
	}
	else
		return (write_error("missing required dining rules."), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
