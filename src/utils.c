/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:52:40 by wlin              #+#    #+#             */
/*   Updated: 2024/05/07 01:35:56 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_philo *philo, char *message, int curr_time)
{
	pthread_mutex_lock(philo->data->mx_end);
	pthread_mutex_lock(philo->data->mx_printf);
	printf("[%d millisec] philo #%d %s\n", curr_time, philo->id, message);
	pthread_mutex_unlock(philo->data->mx_printf);
	pthread_mutex_unlock(philo->data->mx_end);
}
