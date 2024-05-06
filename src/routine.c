/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/05/07 14:29:49 by wlin             ###   ########.fr       */
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

void	ft_sleeping_and_thinking(t_philo *philo)
{
	if (!philo->data->end_flag)
	{
		ft_printf(philo, "is sleeping", ft_time());
	}
	ft_usleep(philo->data->time_to_sleep);
	if (!philo->data->end_flag)
	{
		ft_printf(philo, "is thinking", ft_time());
	}
}

void	ft_eating(t_philo *philo)
{
	int	curr_time;

	pthread_mutex_lock(philo->left_fork);
	curr_time = ft_time();
	if (!philo->data->end_flag)
	{
		ft_printf(philo, "has taken a left fork", curr_time);
	}
	pthread_mutex_lock(philo->right_fork);
	curr_time = ft_time();
	pthread_mutex_lock(philo->data->mx_end);
	philo->ate_at = curr_time;
	pthread_mutex_unlock(philo->data->mx_end);
	if (!philo->data->end_flag)
	{
		ft_printf(philo, "has taken a right fork", curr_time);
		ft_printf(philo, "is eating", curr_time);
		// rule->num_meals--;
	}
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	printf("%p\n", philo);
	printf("%p\n", philo->tid);
	printf("hola %d\n", philo->id);
	while (1)
	{
		ft_eating(philo);
		ft_sleeping_and_thinking(philo);
	}
	return (EXIT_SUCCESS);
}

//PROBLEM:
//all of thread haven eaten 'num_meals' times, then stop the simulation
//while there is still one thread haven't reach 'num_meals' times,
