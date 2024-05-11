/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:19 by wlin              #+#    #+#             */
/*   Updated: 2024/05/11 15:49:47 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_data *data)
{
	int	i;

	i = -1;
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

void	ft_die(t_data *data)
{
	int		i;
	int		is_gonna_die;
	long	ate_at;
	long	time_to_die;
	int	num_meals;

	is_gonna_die = 0;
	while (!is_gonna_die)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(data->mx_info);///
			time_to_die = data->time_to_die;////
			ate_at = data->all_philos->ate_at;////
			num_meals = data->all_philos->num_meals;///
			pthread_mutex_unlock(data->mx_info);////
			if ((ft_time() - ate_at) > time_to_die || num_meals == 0)
			{
				is_gonna_die = 1;
				set_end_flag(data);
				ft_ntb_printf(&data->all_philos[i], "died", ft_time(), NTB);
				// exit(3);
			}
			++i;
		}
		// ft_usleep(5);
	}
}

void	start_dining(t_data *data)
{
	create_thread(data);
	ft_die(data);
}
