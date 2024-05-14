/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:52:40 by wlin              #+#    #+#             */
/*   Updated: 2024/05/12 20:14:36 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end_printf(t_data *data)
{
	pthread_mutex_lock(data->mx_info);
	pthread_mutex_lock(data->mx_printf);
	printf("[%ld ms] All philos are well fed!\n", ft_time() - data->start_at);
	pthread_mutex_unlock(data->mx_printf);
	pthread_mutex_unlock(data->mx_info);
}

void	ft_printf(t_philo *philo, char *message, long curr_time)
{
	ft_ntb_printf(philo, message, curr_time, TB);
	
}

void	ft_ntb_printf(t_philo *philo, char *message, long curr_time, int tbontb)
{
	pthread_mutex_lock(philo->data->mx_end);
	if (!tbontb || !philo->data->end_flag)
	{
		pthread_mutex_lock(philo->data->mx_printf);
		printf("[%ld ms] Philo #%d %s\n", curr_time - philo->data->start_at, philo->id, message);
		pthread_mutex_unlock(philo->data->mx_printf);
	}
	pthread_mutex_unlock(philo->data->mx_end);
}
