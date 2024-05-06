/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/05/06 17:24:14 by wlin             ###   ########.fr       */
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

void	ft_sleeping_and_thinking(t_rule *rule)
{
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		ft_printf(rule, "is sleeping", ft_time());
	}
	pthread_mutex_unlock(rule->mx_die);
	ft_usleep(rule->t_sleep);
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		ft_printf(rule, "is thinking", ft_time());
	}
	pthread_mutex_unlock(rule->mx_die);
}

void	ft_eating(t_rule *rule)
{
	int	curr_time;

	// if (rule->philo_id % 2 != 0)
		// usleep(1);
	pthread_mutex_lock(rule->left_fork);
	curr_time = ft_time();
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		ft_printf(rule, "has taken a left fork", curr_time);
	}
	pthread_mutex_unlock(rule->mx_die);
	pthread_mutex_lock(rule->right_fork);
	curr_time = ft_time();
	pthread_mutex_lock(rule->mx_die);//1
	rule->t_start_eating = curr_time;//1 accessing struct to update start_eating_time
	pthread_mutex_unlock(rule->mx_die);//1
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		ft_printf(rule, "has taken a right fork", curr_time);
		ft_printf(rule, "is eating", curr_time);
		// rule->num_eat--;
	}
	pthread_mutex_unlock(rule->mx_die);
	ft_usleep(rule->t_eat);
	pthread_mutex_unlock(rule->right_fork);
	pthread_mutex_unlock(rule->left_fork);
}

void	*routine(void *data)
{
	t_rule			*rule;

	rule = (t_rule *)data;
	while (1)
	{
		ft_eating(rule);
		ft_sleeping_and_thinking(rule);
	}
	return (EXIT_SUCCESS);
}

//PROBLEM:
//all of thread haven eaten 'num_eat' times, then stop the simulation
//while there is still one thread haven't reach 'num_eat' times,
