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

void	routine(t_rule *rule)
{
	pthread_mutex_t	mutex;
	int	i;

	i = 0;
	thread_mutex_init(&mutex, NULL);
	while (i < rule->n_philo)
	{
		pthread_mutex_lock(&mutex);
		usleep(rule->t_eat);
		printf("%lu philo %d has tacken a fork\n", gettimeofday(), (i + 1));
		pthread_mutex_unlock(&mutex);
	}
}

void	start_dining(t_rule *rule)
{
	pthread_t	*thr;
	int			i;

	i = 0;
	thr = malloc(sizeof(t_rule) * rule->n_philo);
	if (!thr)
		return (NULL);
	while (i < rule->n_philo)
		if (pthread_create(&thr[i++], NULL, &routine, NULL) != 0)
			return (printf("Failed to create thread.\n"), NULL);
}
