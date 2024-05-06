/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:19 by wlin              #+#    #+#             */
/*   Updated: 2024/05/06 17:23:52 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_dining_rules(int argc, char **args, t_rule *rule)
{
	rule->n_philo = ft_atoi(args[1]);
	rule->t_die = ft_atoi(args[2]);
	rule->t_eat = ft_atoi(args[3]);
	rule->t_sleep = ft_atoi(args[4]);
	if (argc == 6)
		rule->num_eat = ft_atoi(args[5]);
}

t_rule	struct_copy(t_rule rule, int philo_id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, pthread_mutex_t *mx_printf, pthread_mutex_t *mx_die)
{
	t_rule			philo;

	philo.n_philo = rule.n_philo;
	philo.t_die = rule.t_die;
	philo.t_eat = rule.t_eat;
	philo.t_sleep = rule.t_sleep;
	philo.num_eat = rule.num_eat; ///TODO: handle if this value is not set
	philo.philo_id = philo_id;
	philo.left_fork = left_fork;
	philo.right_fork = right_fork;
	philo.mx_printf = mx_printf;
	philo.mx_die = mx_die;
	philo.die_flag = 0;
	return (philo);
}

pthread_t	create_thread(t_rule *rule, int i)
{
	pthread_t	thr;

	if (pthread_create(&thr, NULL, &routine, &rule[i]) != 0)
	{
		printf("Failed to create thread.\n");
		return (NULL);
	}
	return (thr);
}

void	ft_die(t_rule *all_rule, pthread_t *threads)
{
	int	i;
	int	is_gonna_die;
	int	time_start_eating;
	int	time_die;
	int	j;
	int	num_eat;

	i = 0;
	is_gonna_die = 0;
	while (!is_gonna_die)
	{
		while (i < all_rule[i].n_philo)
		{
			pthread_mutex_lock(all_rule[i].mx_die);
			time_die = all_rule[i].t_die;
			time_start_eating = all_rule[i].t_start_eating;
			num_eat = all_rule[i].num_eat;
			pthread_mutex_unlock(all_rule[i].mx_die);
			if ((ft_time() - time_start_eating) > time_die || num_eat == 0)
			{
				is_gonna_die = 1;
				pthread_mutex_lock(all_rule[i].mx_die);
				j = 0;
				all_rule[j].die_flag = 1;
				ft_printf(&all_rule[i], "died", ft_time());
				pthread_mutex_unlock(all_rule[i].mx_die);
				// (void)threads;
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

int	start_dining(t_rule *all_rule, int n_philo)
{
	pthread_t	*thr;
	int			i;

	i = 0;
	thr = malloc(sizeof(pthread_t) * n_philo);
	if (!thr)
		return (EXIT_FAILURE);
	while (i < n_philo)
	{
		all_rule[i].t_start_eating = ft_time();
		thr[i] = create_thread(all_rule, i);
		i++;
	}
	ft_die(all_rule, thr);
	// i = 0;
	// while (i < n_philo)
	// {
	// 	pthread_join(thr[i++], NULL);
	// }
	return (EXIT_SUCCESS);
}
