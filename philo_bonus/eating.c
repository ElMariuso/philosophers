/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:58:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/19 13:23:10 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo, t_rules *rules)
{
	sem_wait(rules->forks);
	print_action(rules, philo, philo->id, "has taken a fork");
	if (rules->nb_philo == 1)
	{
		while (death_checker(rules, philo) != 1)
		{
		}
		sem_post(rules->forks);
		return ;
	}
	sem_wait(rules->forks);
	print_action(rules, philo, philo->id, "has taken a fork");
	sem_wait(rules->data_race_checker);
	philo->last_meal = get_current_timestamp();
	sem_post(rules->data_race_checker);
	print_action(rules, philo, philo->id, "is eating");
	better_usleep(rules->time_to_eat * 1000, rules, philo);
	sem_wait(rules->data_race_checker);
	philo->nb_eat++;
	sem_post(rules->data_race_checker);
	sem_post(rules->forks);
	sem_post(rules->forks);
}
