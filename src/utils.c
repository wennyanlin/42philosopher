/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:52:40 by wlin              #+#    #+#             */
/*   Updated: 2024/05/11 15:39:41 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("[%ld millisec] philo #%d %s\n", curr_time, philo->id, message);
		pthread_mutex_unlock(philo->data->mx_printf);
	}
	pthread_mutex_unlock(philo->data->mx_end);
}
