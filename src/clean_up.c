/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:02:05 by wlin              #+#    #+#             */
/*   Updated: 2024/05/17 14:40:03 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_up(t_data *data, pthread_mutex_t *all_forks)
{
    int		i;

    i = -1;
    while (++i < data->num_philos)
		pthread_mutex_destroy(data->all_philos[i].left_fork);
    pthread_mutex_destroy(data->mx_end);
    pthread_mutex_destroy(data->mx_info);
    pthread_mutex_destroy(data->mx_printf);
    free(data->all_philos);
    free(all_forks);
    free(data->mx_end);
    free(data->mx_info);
    free(data->mx_printf);
}