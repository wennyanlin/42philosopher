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

t_rule	struct_copy(t_rule rule, int philo_id, pthread_mutex_t	*mutex)
{
	t_rule	philo;

	philo.n_philo = rule.n_philo;
	philo.t_die = rule.t_die;
	philo.t_eat = rule.t_eat;
	philo.t_sleep = rule.t_sleep;
	philo.n_time_to_eat = rule.n_time_to_eat; ///TODO: handle if this value is not set
	philo.philo_id = philo_id;
	philo.mutex = mutex;
	return (philo);
}

void	print_struct(t_rule rule, t_rule philo_rule)
{
	printf("===========================RULE==============================\n\n");
	printf("rule.n_philo: %d\n", rule.n_philo);
	printf("rule.t_die: %d\n", rule.t_die);
	printf("rule.t_eat: %d\n", rule.t_eat);
	printf("rule.t_sleep: %d\n", rule.t_sleep);
	printf("rule.n_time_to_eat: %d\n", rule.n_time_to_eat);
	printf("rule.philo_id: %d\n", rule.philo_id);
	printf("========================PHILO_RULE===========================\n\n");
	printf("philo_rule.n_philo: %d\n", philo_rule.n_philo);
	printf("philo_rule.t_die: %d\n", philo_rule.t_die);
	printf("philo_rule.t_eat: %d\n", philo_rule.t_eat);
	printf("philo_rule.t_sleep: %d\n", philo_rule.t_sleep);
	printf("philo_rule.n_time_to_eat: %d\n", philo_rule.n_time_to_eat);
	printf("philo_rule.philo_id: %d\n\n", philo_rule.philo_id);
	printf("============================================================\n\n");

}

void	*routine(void *data)
{
	struct timeval	curr_time;
	t_rule			*rule;

	rule = (t_rule *)data;
	printf("philo_%d waiting for forks\n", rule->philo_id);
	pthread_mutex_lock(rule->mutex);
	gettimeofday(&curr_time, NULL);
	printf("At %dms philo_%d has taken a fork\n", curr_time.tv_usec, rule->philo_id);
	usleep(rule->t_eat);
	pthread_mutex_unlock(rule->mutex);
	printf("philo_%d dropped forks\n", rule->philo_id);

	return (EXIT_SUCCESS);
}

pthread_t	create_thread(t_rule *rule, int i)
{
	pthread_t	thr;

	printf("creating thread for philo_%d\n", rule[i].philo_id);

	if (pthread_create(&thr, NULL, &routine, &rule[i]) != 0)
	{
		printf("Failed to create thread.\n");
		return (NULL);
	}
	return (thr);
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
		thr[i] = create_thread(all_rule, i);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		printf("waiting philo_%d to finish\n", i + 1);
		pthread_join(thr[i++], NULL);
	}
	return (EXIT_SUCCESS);
}
