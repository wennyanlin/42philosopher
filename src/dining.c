#include "philo.h"

void	get_dining_rules(int argc, char **args, t_rule *rule)
{
	rule->n_philo = ft_atoi(args[1]);
	rule->t_die = ft_atoi(args[2]);
	rule->t_eat = ft_atoi(args[3]);
	rule->t_sleep = ft_atoi(args[4]);
	if (argc == 6)
		rule->n_time_to_eat = ft_atoi(args[5]);
}

void	*routine(void *data)
{
	struct timeval	curr_time;
	pthread_mutex_t	mutex;
	t_rule			*rule;

	rule = (t_rule *)data;
	pthread_mutex_lock(&mutex);
	gettimeofday(&curr_time, NULL);
	printf("%d philo_%d has taken a fork\n", curr_time.tv_usec, rule->philo_id);
	usleep(rule->t_eat);
	pthread_mutex_unlock(&mutex);
	return (EXIT_SUCCESS);
}

int	start_dining(t_rule *rule)
{
	pthread_t	*thr;
	int			i;

	i = 0;
	thr = malloc(sizeof(t_rule) * rule->n_philo);
	if (!thr)
		return (EXIT_FAILURE);
	while (i < rule->n_philo)
	{
		rule->philo_id = i + 1;
		if (pthread_create(&thr[i], NULL, &routine, rule) != 0)
		{
			printf("Failed to create thread.\n");
			return (EXIT_FAILURE);
		}
		pthread_join(thr[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
