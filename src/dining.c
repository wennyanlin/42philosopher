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


