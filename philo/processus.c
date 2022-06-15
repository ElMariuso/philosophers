/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:48:18 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 15:13:18 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void	*arg)
{
	t_philo			*philo;
	t_rules			*rules;
	int				left_id;
	int				right_id;

	philo = (t_philo *) arg;
	rules = philo->rules;
	left_id = philo->id;
	if (philo->id == 0)
		right_id = philo->rules->nb_philo - 1;
	else
		right_id = left_id - 1;
	if (philo->id % 2 != 0)
		better_usleep((rules->time_to_eat * 1000) / 2, rules);
	while (death_checker(rules) != 1 && eat_checker(rules) != 1)
	{
		eating(philo, rules, left_id, right_id);
		if (death_checker(rules) == 1 || eat_checker(rules) == 1)
			break ;
		print_action(rules, philo->id, "is sleeping");
		better_usleep(rules->time_to_sleep * 1000, rules);
		print_action(rules, philo->id, "is thinking");
		usleep(500);
	}
	return (NULL);
}

void	is_anyone_dead(t_rules *rules)
{
	int	i;

	i = 0;
	while (eat_checker(rules) != 1 && death_checker(rules) != 1)
	{
		while (i != rules->nb_philo)
		{
			pthread_mutex_lock(&rules->data_race_checker);
			if (time_diff(rules->philo[i].last_meal,
					get_current_timestamp()) > rules->time_to_die)
			{
				printf("%lld %d died\n", time_diff(rules->base_timestamp,
						get_current_timestamp()), rules->philo[i].id + 1);
				rules->someone_died = true;
				pthread_mutex_unlock(&rules->data_race_checker);
				break ;
			}
			pthread_mutex_unlock(&rules->data_race_checker);
			i++;
		}
		i = 0;
	}
}

int	ft_processus(t_rules *rules)
{
	int	i;
	int	er;

	i = 0;
	er = 0;
	while (i < rules->nb_philo)
	{
		er = pthread_create(&rules->philo[i].thread, NULL,
				(void *)routine, (void *)&rules->philo[i]);
		if (er != 0)
			return (1);
		i++;
	}
	is_anyone_dead(rules);
	er = leave(rules);
	if (er == 1)
		return (1);
	return (0);
}
