/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:08:22 by wlin              #+#    #+#             */
/*   Updated: 2024/04/25 11:56:14 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define NC	"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define TRUE 1
# define FALSE 0
# define MAX_INT 2147483647

typedef struct s_rule
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_time_to_eat;
}	t_rule;

typedef	struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}	t_locks;


int	validate_args(int argc, char **argv);
long	ft_atoi(const char *str);
int		is_number(char *arg);

void	get_dining_rules(int argc, char **args, t_rule *rule);


#endif

