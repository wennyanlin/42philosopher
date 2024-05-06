/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:52:40 by wlin              #+#    #+#             */
/*   Updated: 2024/05/06 17:00:28 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_rule *rule, char *message, int curr_time)
{
	pthread_mutex_lock(rule->mx_printf);
	printf("[%d millisec] philo #%d %s\n", curr_time, rule->philo_id, message);
	pthread_mutex_unlock(rule->mx_printf);
}
