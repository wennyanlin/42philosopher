/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:08:22 by wlin              #+#    #+#             */
/*   Updated: 2024/05/17 13:41:52 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

# define NC	"\e[0m"
# define YELLOW	"\e[33m"
# define BYELLOW	"\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define TRUE 1
# define FALSE 0
# define MAX_INT 2147483647
# define NTB 0
# define TB 1

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				num_meals;
	long			ate_at;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_meals;
	int				meals_flag;
	long			start_at;
	int				end_flag;
	int				all_fed;
	t_philo			*all_philos;
	pthread_mutex_t	*mx_info;
	pthread_mutex_t	*mx_printf;
	pthread_mutex_t	*mx_end;
}	t_data;

int		validate_dining_rules(int argc, char **argv);
long	ft_atoi(const char *str);
int		is_number(char *arg);
// void	get_dining_rules(int argc, char **args, t_philo *rule);
void	dining_start(t_data *data);
pthread_mutex_t	*philo_prepare(t_data *data);
void	*routine(void *data);
void	ft_eating(t_philo *rule);
long	ft_time(void);
void	monitor(t_data *data);
void	ft_usleep(long millisec);
void	ft_printf(t_philo *rule, char *message, long curr_time);
void	ft_ntb_printf(t_philo *philo, char *message, long curr_time, int tbontb);
void	ft_end_printf(t_data *data);
void	*one_philo_routine(void *data);
void    clean_up(t_data *data, pthread_mutex_t *all_forks);

#endif
