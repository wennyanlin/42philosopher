/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/04/29 22:49:20 by wlin             ###   ########.fr       */
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
	long int	millisec;

	// if (rule->philo_id % 2 != 0)
	// 	usleep(1);
	pthread_mutex_lock(rule->left_fork);
	millisec = ft_time();
	printf("[%ld millisec] philo #%d has taken a left fork\n", millisec, rule->philo_id);
	pthread_mutex_lock(rule->right_fork);
	millisec = ft_time();
	printf("[%ld millisec] philo #%d has taken a right fork\n", millisec, rule->philo_id);
	ft_usleep(rule->t_eat);
	pthread_mutex_unlock(rule->right_fork);
	millisec = ft_time();
	printf("[%ld millisec] philo #%d dropped right fork\n", millisec, rule->philo_id);
	pthread_mutex_unlock(rule->left_fork);
	millisec = ft_time();
	printf("[%ld millisec] philo #%d dropped left fork\n", millisec, rule->philo_id);
}

void	*routine(void *data)
{
	t_rule			*rule;

	rule = (t_rule *)data;
	ft_eating(rule);
	return (EXIT_SUCCESS);
}
