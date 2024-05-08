/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:23:58 by wlin              #+#    #+#             */
/*   Updated: 2024/05/08 18:35:59 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error()
{
	printf("Error\n");
}

pthread_mutex_t *create_forks_array(t_data *data)
{
	pthread_mutex_t		*all_forks;
	int				i;

	all_forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!all_forks)
		return (NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&all_forks[i], NULL);
	//TODO: return a specified error message!
	return (all_forks);
}

void	struct_copy(t_data *data, pthread_mutex_t *all_forks)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->end_flag = 0;
		data->all_philos[i].id = i + 1;
		data->all_philos[i].num_meals = data->num_meals; ///TODO: handle if this value is not set
		data->all_philos[i].left_fork = &all_forks[i];
		if (i == data->num_philos - 1)
			data->all_philos[i].right_fork = &all_forks[0];
		else
			data->all_philos[i].right_fork = &all_forks[i + 1];
		data->all_philos[i].data = data;
	}
}

int	get_all_philos_rules(t_data *data, int argc, char **args)
{
	pthread_mutex_t	*all_forks;

	data->num_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->end_flag = 0;
	if (argc == 6)
		data->num_meals = ft_atoi(args[5]);///TODO: handle if this value is not set!
	data->all_philos = malloc(sizeof(t_philo) * (data->num_philos));
	if (!data->all_philos)
		return (2);
	all_forks = create_forks_array(data);
	data->mx_printf = malloc(sizeof(pthread_mutex_t));
	data->mx_end = malloc(sizeof(pthread_mutex_t));
	data->mx_info = malloc(sizeof(pthread_mutex_t));
	if (!data->mx_end || !data->mx_info || !data->mx_printf)
		return (3);
	pthread_mutex_init(data->mx_printf, NULL);
	pthread_mutex_init(data->mx_end, NULL);
	pthread_mutex_init(data->mx_info, NULL);
	struct_copy(data, all_forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		i = -1;
		if (validate_args(argc, argv) == FALSE)
			return (write_error(), EXIT_FAILURE);
		get_all_philos_rules(&data, argc, argv);
		start_dining(&data);
		while (++i < data.num_philos)
			pthread_mutex_destroy(data.all_philos[i].left_fork);
	}
	else
		write_error();
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.all_philos[i].tid, NULL);
	return (0);
}
