/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:19 by wlin              #+#    #+#             */
/*   Updated: 2024/05/14 13:43:40 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_at = ft_time();
	while (++i < data->num_philos)
	{
		data->all_philos[i].ate_at = ft_time();
		if (pthread_create(&data->all_philos[i].tid, NULL, &routine, &data->all_philos[i]) != 0)
		{
			printf("Failed to create thread.\n");
			return ;
		}
	}
}
void	set_end_flag(t_data *data)
{
	pthread_mutex_lock(data->mx_end);
	data->end_flag = 1;
	pthread_mutex_unlock(data->mx_end);
}

int	are_fed(t_data *data)
{
	int	i;
	int	num_meals;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(data->mx_info);
		num_meals = data->all_philos[i].num_meals;
		pthread_mutex_unlock(data->mx_info);
		if (num_meals != 0)
			return (0);
	}
	data->all_fed = 1;
	return (1);
}

int	are_starved(t_data *data, int i)
{
	long	time_to_die;
	long	ate_at;

	pthread_mutex_lock(data->mx_info);///
	time_to_die = data->time_to_die;////
	ate_at = data->all_philos[i].ate_at;////
	pthread_mutex_unlock(data->mx_info);////
	if ((ft_time() - ate_at) > time_to_die)
		return (1);
	return (0);
}

void	ft_die(t_data *data)
{
	int	i;
	int	is_gonna_die;

	is_gonna_die = 0;
	while (!is_gonna_die)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (are_starved(data, i) || (data->meals_flag && are_fed(data)))
			{
				is_gonna_die = 1;
				set_end_flag(data);
				if (data->all_fed)
					return (ft_end_printf(data));
				ft_ntb_printf(&data->all_philos[i], "died", ft_time(), NTB);
				return ;
			}
		}
		ft_usleep(5);
	}
}

void	start_dining(t_data *data)
{
	if (data->num_philos == 1)
	{
		if (pthread_create(&data->all_philos[0].tid, NULL, &one_philo_routine, &data->all_philos[0]) != 0)
			printf("Failed to create thread.\n");
	}
	else
	{
		create_thread(data);
		ft_die(data);
	}
	return ;
}
