/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:52:40 by wlin              #+#    #+#             */
/*   Updated: 2024/05/18 12:09:13 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end_printf(t_data *data)
{
	pthread_mutex_lock(&data->mtx_info);
	pthread_mutex_lock(&data->mtx_printf);
	printf("[%ld ms] All philos are well fed!\n", ft_time() - data->start_at);
	pthread_mutex_unlock(&data->mtx_printf);
	pthread_mutex_unlock(&data->mtx_info);
}

void	ft_printf(t_philo *philo, char *message, long curr_time)
{
	ft_ntb_printf(philo, message, curr_time, TB);
}

void	ft_ntb_printf(t_philo *philo, char *message, long curr_time, int tbontb)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	if (!tbontb || !philo->data->end_flag)
	{
		pthread_mutex_lock(&philo->data->mtx_printf);
		printf("[%ld ms] #%d %s\n", curr_time - philo->data->start_at,
			philo->id, message);
		pthread_mutex_unlock(&philo->data->mtx_printf);
	}
	pthread_mutex_unlock(&philo->data->mtx_end);
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long millisec)
{
	long	end;

	end = ft_time() + millisec;
	while (ft_time() < end)
		usleep(200);
}
