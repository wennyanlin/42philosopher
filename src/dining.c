/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:19 by wlin              #+#    #+#             */
/*   Updated: 2024/05/07 22:12:33 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		// printf("philo %d: %p-%p\n", (i + 1), data->all_philos[i].left_fork, data->all_philos[i].right_fork);
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
	int	i;
	int	is_gonna_die;
	int	ate_at;
	int	time_to_die;
	int	j;
	int	num_meals;

	i = 0;
	is_gonna_die = 0;
	while (!is_gonna_die)
	{
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
				j = 0;
				set_end_flag(data);
				ft_ntb_printf(&data->all_philos[j], "died", ft_time(), NTB);
				i = 0;
				while (i < data->num_philos)
					pthread_detach(data->all_philos[i++].tid);
			}
			if (i == data->num_philos - 1)
				i = 0;
			else
				i++;
		}
		ft_usleep(5);
	}
}

void	create_thread(t_data *data)
{
	int	i;

	i = -1;
	// printf("data->n_philos %d\n", data->num_philos);
	while (++i < data->num_philos)
	{
		data->all_philos[i].ate_at = ft_time();
		// printf("%d, %d, %d, %d, %d, %d, %d\n", data->num_philos, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->num_meals, data->start_at, data->end_flag);
		// printf("%p, %p, %p, %p\n", data->all_philos, data->mx_info, data->mx_printf, data->mx_end);
		if (pthread_create(&data->all_philos[i].tid, NULL, &routine, &data->all_philos[i]) != 0)
		{
			printf("Failed to create thread.\n");
			return ;
		}
	}
}

int	start_dining(t_data *data)
{
	// while (i < data->num_philos)
	// {
		// data->all_philos[i].ate_at = ft_time();
		/*data->all_threads = malloc(sizeof(pthread_t) * (data->num_philos));
		if (!data->all_threads)
			return (EXIT_FAILURE);*/
		//memset(data->all_threads, 0, sizeof(pthread_t));
	create_thread(data);
		// i++;
	// }
	ft_die(data);
	// i = 0;
	// while (i < num_philos)
	// {
	// 	pthread_join(thr[i++], NULL);
	// }
	return (EXIT_SUCCESS);
}
