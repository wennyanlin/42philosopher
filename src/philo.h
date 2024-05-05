/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:08:22 by wlin              #+#    #+#             */
/*   Updated: 2024/05/05 23:16:19 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

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
	int	num_eat;
	int	philo_id;
	int	t_start_routine;
	int	t_start_eating;
	int	t_fin_eating;
	int	die_flag;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mx_printf;
	pthread_mutex_t	*mx_die;

}	t_rule;

int		validate_args(int argc, char **argv);
long	ft_atoi(const char *str);
int		is_number(char *arg);
void	get_dining_rules(int argc, char **args, t_rule *rule);
int		start_dining(t_rule *all_rules, int n_philo);
t_rule	struct_copy(t_rule rule, int philo_id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, pthread_mutex_t *mx_printf, pthread_mutex_t *mx_die);
void	*routine(void *data);
void	ft_eating(t_rule *rule);
int		ft_time(void);
void	ft_die(t_rule *all_rule, pthread_t *threads);
void	ft_usleep(int millisec);

#endif
