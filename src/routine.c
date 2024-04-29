/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/04/29 16:13:41 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int millisec)
{
	int	end;

	end = ft_time() + millisec;
	while (ft_time() < end)
		usleep(200);
}

void	ft_eating(t_rule *rule)
{
	long int	milisec;

	// if (rule->philo_id % 2 != 0)
	// 	usleep(100);
	pthread_mutex_lock(rule->mutex);
	milisec = ft_time();
	printf("[%ld milisec] philo_%d has taken a fork\n", milisec, rule->philo_id);
	ft_usleep(rule->t_eat);
	pthread_mutex_unlock(rule->mutex);
	printf("[%ld milisec] philo_%d dropped forks\n", milisec, rule->philo_id);
}

void	*routine(void *data)
{
	t_rule			*rule;

	rule = (t_rule *)data;
	ft_eating(rule);
	return (EXIT_SUCCESS);
}
