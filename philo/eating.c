/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:47:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 14:50:40 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo, t_rules *rules, int first, int second)
{
	pthread_mutex_lock(&rules->forks[first]);
	print_action(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&rules->forks[second]);
	print_action(rules, philo->id, "has taken a fork");
}

void	eating_first(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	take_forks(philo, rules, left_id, right_id);
	pthread_mutex_lock(&rules->data_race_checker);
	philo->last_meal = get_current_timestamp();
	pthread_mutex_unlock(&rules->data_race_checker);
	print_action(rules, philo->id, "is eating");
	better_usleep(rules->time_to_eat * 1000, rules);
}

void	eating_second(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	take_forks(philo, rules, right_id, left_id);
	pthread_mutex_lock(&rules->data_race_checker);
	philo->last_meal = get_current_timestamp();
	pthread_mutex_unlock(&rules->data_race_checker);
	print_action(rules, philo->id, "is eating");
	better_usleep(rules->time_to_eat * 1000, rules);
}

void	eating(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	if (philo->id % 2 == 0)
		eating_first(philo, rules, left_id, right_id);
	else
		eating_second(philo, rules, left_id, right_id);
	pthread_mutex_lock(&rules->data_race_checker);
	philo->nb_eat++;
	if (philo->nb_eat == rules->nb_time_philo_eat)
		rules->nb_philo_eat_all++;
	pthread_mutex_unlock(&rules->data_race_checker);
	pthread_mutex_unlock(&rules->forks[left_id]);
	pthread_mutex_unlock(&rules->forks[right_id]);
}
