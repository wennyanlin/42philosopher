/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/05/18 17:40:33 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_end_flag(t_data *data)
{
	int	end_flag;

	pthread_mutex_lock(&data->mtx_end);
	end_flag = data->end_flag;
	pthread_mutex_unlock(&data->mtx_end);
	return (end_flag);
}

void	ft_sleeping_and_thinking(t_philo *philo)
{
	ft_printf(philo, "is sleeping", ft_time());
	ft_usleep(philo->data->time_to_sleep);
	ft_printf(philo, "is thinking", ft_time());
}

void	ft_eating(t_philo *philo)
{
	long	curr_time;

	pthread_mutex_lock(philo->left_fork);
	curr_time = ft_time();
	ft_printf(philo, "has taken a left fork", curr_time);
	pthread_mutex_lock(philo->right_fork);
	curr_time = ft_time();
	pthread_mutex_lock(&philo->mtx_time);
	philo->ate_at = curr_time;
	pthread_mutex_unlock(&philo->mtx_time);
	ft_printf(philo, "has taken a right fork", curr_time);
	ft_printf(philo, "is eating", curr_time);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->mtx_meal);
	if (philo->num_meals > 0)
		philo->num_meals--;
	pthread_mutex_unlock(&philo->mtx_meal);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (get_end_flag(philo->data) == 0)
	{
		ft_eating(philo);
		ft_sleeping_and_thinking(philo);
	}
	return (EXIT_SUCCESS);
}

void	*one_philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	ft_printf(philo, "has taken a left fork", ft_time());
	ft_usleep(philo->data->time_to_die);
	ft_ntb_printf(philo, "died", ft_time(), NTB);
	return (EXIT_SUCCESS);
}
