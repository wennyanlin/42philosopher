/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:53:52 by wlin              #+#    #+#             */
/*   Updated: 2024/05/05 22:57:41 by wlin             ###   ########.fr       */
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

void	ft_die(t_rule *all_rule, pthread_t *threads)
{
	int	i;
	int	is_gonna_die;
	int	time_start_eating;
	int	time_die;
	int	j;
	
	i = 0;
	is_gonna_die = 0;
	while (!is_gonna_die)
	{
		while (i < all_rule[i].n_philo)
		{
			pthread_mutex_lock(all_rule[i].mx_die);
			time_die = all_rule[i].t_die;
			time_start_eating = all_rule[i].t_start_eating;
			pthread_mutex_unlock(all_rule[i].mx_die);
			if ((ft_time() - time_start_eating) > time_die)
			{
				is_gonna_die = 1;
				pthread_mutex_lock(all_rule[i].mx_die);
				j = 0;
				all_rule[j].die_flag = 1;
				while (j < all_rule[j].n_philo)
					all_rule[j++].die_flag = 1;
				pthread_mutex_lock(all_rule[i].mx_printf);
				printf("[%d millisec] philo #%d died, [%dms], flag: %d\n", ft_time(), i + 1, (ft_time() - time_start_eating), all_rule[i].die_flag);
				pthread_mutex_unlock(all_rule[i].mx_printf);
				pthread_mutex_unlock(all_rule[i].mx_die);
				i = 0;
				while (i < all_rule[i].n_philo)
					pthread_detach(threads[i++]);
			}
			if (i == all_rule[0].n_philo - 1)
				i = 0;
			else
				i++;
		}
		ft_usleep(5);
	}
}

void	ft_sleeping_and_thinking(t_rule *rule)
{
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		pthread_mutex_lock(rule->mx_printf);
		printf("[%d millisec] philo #%d is sleeping, flag: %d\n", ft_time(), rule->philo_id, rule->die_flag);
		pthread_mutex_unlock(rule->mx_printf);
	}
	pthread_mutex_unlock(rule->mx_die);
	ft_usleep(rule->t_sleep);
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		pthread_mutex_lock(rule->mx_printf);
		printf("[%d millisec] philo #%d is thinking, flag: %d\n", ft_time(), rule->philo_id, rule->die_flag);
		pthread_mutex_unlock(rule->mx_printf);
	}
	pthread_mutex_unlock(rule->mx_die);
}

void	ft_eating(t_rule *rule)
{
	long int	millisec;

	// if (rule->philo_id % 2 != 0)
		// usleep(1);
	pthread_mutex_lock(rule->left_fork);
	millisec = ft_time();
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		pthread_mutex_lock(rule->mx_printf);
		printf("[%ld millisec] philo #%d has taken a left fork\n", millisec, rule->philo_id);
		pthread_mutex_unlock(rule->mx_printf);
	}
	pthread_mutex_unlock(rule->mx_die);
	pthread_mutex_lock(rule->right_fork);
	millisec = ft_time();
	pthread_mutex_lock(rule->mx_die);
	rule->t_start_eating = millisec;
	pthread_mutex_unlock(rule->mx_die);
	pthread_mutex_lock(rule->mx_die);
	if (!rule->die_flag)
	{
		pthread_mutex_lock(rule->mx_printf);
		printf("[%ld millisec] philo #%d has taken a right fork\n", millisec, rule->philo_id);
		printf("[%ld millisec] philo #%d is eating\n", millisec, rule->philo_id);
		pthread_mutex_unlock(rule->mx_printf);
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
//when a thread died, it's still doing the routine
//when a thread died, the program still proccesing