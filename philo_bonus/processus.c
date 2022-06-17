/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:57:37 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 19:13:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_dead(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	while (death_checker(rules, philo) != 1 && end_checker(rules) != 1)
	{
		sem_wait(rules->data_race_checker);
		if (time_diff(philo->last_meal,
				get_current_timestamp()) > rules->time_to_die)
		{
			printf("%lld %d died\n",
				time_diff(rules->base_timestamp,
					get_current_timestamp()), philo->id + 1);
			philo->is_dead = true;
			sem_post(rules->death);
			sem_post(rules->data_race_checker);
			break ;
		}
		sem_post(rules->data_race_checker);
	}
	return (NULL);
}

void	*is_finished_thread(void *arg)
{
	int		i;
	t_rules	*rules;

	i = 0;
	rules = (t_rules *)arg;
	sem_wait(rules->finish);
	rules->is_finished = true;
	return (NULL);
}

void	routine_philo(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	create_thread_proc(rules, philo);
	if (philo->id % 2 != 0)
		better_usleep((rules->time_to_eat * 1000) / 2, rules, philo);
	while (death_checker(rules, philo) != 1 && end_checker(rules) != 1)
	{
		eating(philo, rules);
		sem_wait(rules->data_race_checker);
		if (philo->nb_eat == rules->nb_time_philo_eat)
			sem_post(rules->eat);
		sem_post(rules->data_race_checker);
		if (end_checker(rules) == 1)
			break ;
		print_action(rules, philo, philo->id, "is sleeping");
		better_usleep(rules->time_to_sleep * 1000, rules, philo);
		if (end_checker(rules) == 1)
			break ;
		print_action(rules, philo, philo->id, "is thinking");
	}
	destroy_thread_proc(rules, philo);
	free(rules->philo);
	exit(EXIT_SUCCESS);
}

void	processus(t_rules *rules)
{
	int	i;

	i = 0;
	while (i != rules->nb_philo)
	{
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == -1)
			leave_all_and_error(rules, i,
				"Something happened when initializing");
		if (rules->philo[i].pid == 0)
			routine_philo(&rules->philo[i]);
		i++;
	}
}
