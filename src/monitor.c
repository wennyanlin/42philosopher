/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:19 by wlin              #+#    #+#             */
/*   Updated: 2024/05/17 18:41:27 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag(t_data *data)
{
	pthread_mutex_lock(data->mx_end);
	data->end_flag = TRUE;
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
			return (FALSE);
	}
	data->all_fed = TRUE;
	return (TRUE);
}

int	are_starved(t_data *data, int i)
{
	long	time_to_die;
	long	ate_at;

	pthread_mutex_lock(data->mx_info);
	time_to_die = data->time_to_die;
	ate_at = data->all_philos[i].ate_at;
	pthread_mutex_unlock(data->mx_info);
	if ((ft_time() - ate_at) > time_to_die)
		return (TRUE);
	return (FALSE);
}

void	monitor(t_data *data)
{
	int	i;
	int	is_gonna_die;

	is_gonna_die = 0;
	while (!is_gonna_die)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (are_starved(data, i) || (data->has_meal_limit && are_fed(data)))
			{
				is_gonna_die = 1;
				set_end_flag(data);
				if (data->all_fed)
					return (ft_end_printf(data));
				ft_ntb_printf(&data->all_philos[i], "died", ft_time(), NTB);
				return ;
			}
		}
	}
}

void	simulation(t_data *data)
{
	int	i;

	i = -1;
	data->start_at = ft_time();
	while (++i < data->num_philos)
	{
		data->all_philos[i].ate_at = ft_time();
		if (data->all_philos[i].id % 2 == 0)
			ft_usleep(10);
		if (pthread_create(&data->all_philos[i].tid, NULL, &routine,
				&data->all_philos[i]) != 0)
		{
			printf("Failed to create thread.\n");
			return ;
		}
	}
}
