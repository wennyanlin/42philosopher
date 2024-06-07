/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:53:57 by wlin              #+#    #+#             */
/*   Updated: 2024/05/18 17:40:41 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_init(&data->all_philos[i].mtx_meal, NULL);
		pthread_mutex_init(&data->all_philos[i].mtx_time, NULL);
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
	data->all_fed = FALSE;
	data->has_meal_limit = FALSE;
	if (argc == 6)
	{
		data->num_meals = ft_atoi(args[5]);
		data->has_meal_limit = TRUE;
	}
	pthread_mutex_init(&(data->mtx_printf), NULL);
	pthread_mutex_init(&(data->mtx_end), NULL);
	pthread_mutex_init(&(data->mtx_info), NULL);
	all_forks = philo_prepare(data);
	return (all_forks);
}
