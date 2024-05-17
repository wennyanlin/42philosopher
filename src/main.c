/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/05/17 14:15:32 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

pthread_mutex_t	*philo_prepare(t_data *data)
{
	int					i;
	pthread_mutex_t		*all_forks;
	
	data->all_philos = malloc(sizeof(t_philo) * (data->num_philos));
	all_forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!all_forks || !data->all_philos)
		return (NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&all_forks[i], NULL);
	i = -1;
	while (++i < data->num_philos)
	{
		data->all_philos[i].id = i + 1;
		data->all_philos[i].num_meals = data->num_meals;
		data->all_philos[i].left_fork = &all_forks[i];
		if (i == data->num_philos - 1)
			data->all_philos[i].right_fork = &all_forks[0];
		else
			data->all_philos[i].right_fork = &all_forks[i + 1];
		data->all_philos[i].data = data;
	}
	return (all_forks);
}

pthread_mutex_t	*dining_prepare(t_data *data, int argc, char **args)
{
	pthread_mutex_t	*all_forks;
	
	data->num_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->num_meals = 0;
	data->end_flag = 0;
	data->all_fed = 0;
	data->meals_flag = 0;
	if (argc == 6)
	{
		data->num_meals = ft_atoi(args[5]);
		data->meals_flag = 1;
	}
	data->mx_printf = malloc(sizeof(pthread_mutex_t));
	data->mx_end = malloc(sizeof(pthread_mutex_t));
	data->mx_info = malloc(sizeof(pthread_mutex_t));
	if (!data->mx_end || !data->mx_info || !data->mx_printf)
		return (NULL);
	pthread_mutex_init(data->mx_printf, NULL);
	pthread_mutex_init(data->mx_end, NULL);
	pthread_mutex_init(data->mx_info, NULL);
	all_forks = philo_prepare(data);
	return (all_forks);
}

int	main(int argc, char **argv)
{
	t_data	data;
	pthread_mutex_t	*all_forks;
	
	int		i;

	if (argc == 5 || argc == 6)
	{
		if (validate_dining_rules(argc, argv) == FALSE)
			return (write_error(), EXIT_FAILURE);
		all_forks = dining_prepare(&data, argc, argv);
		dining_start(&data);
	}
	else
		write_error();
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.all_philos[i].tid, NULL);
	clean_up(&data, all_forks);
	return (0);
}
