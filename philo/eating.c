/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:47:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/19 13:17:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo, t_rules *rules, int first, int second)
{
	pthread_mutex_lock(&rules->forks[first]);
	print_action(rules, philo->id, "has taken a fork");
	if (rules->nb_philo == 1)
	{
		while (death_checker(rules) != 1)
		{
		}
		return (1);
	}
	else
	{
		pthread_mutex_lock(&rules->forks[second]);
		print_action(rules, philo->id, "has taken a fork");
	}
	return (0);
}

int	eating_first(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	int	er;

	er = take_forks(philo, rules, left_id, right_id);
	if (er == 1)
	{
		pthread_mutex_unlock(&rules->forks[left_id]);
		if (rules->nb_philo != 1)
			pthread_mutex_unlock(&rules->forks[right_id]);
		return (1);
	}
	pthread_mutex_lock(&rules->data_race_checker);
	philo->last_meal = get_current_timestamp();
	pthread_mutex_unlock(&rules->data_race_checker);
	print_action(rules, philo->id, "is eating");
	better_usleep(rules->time_to_eat * 1000, rules);
	return (0);
}

int	eating_second(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	int	er;

	er = take_forks(philo, rules, right_id, left_id);
	if (er == 1)
	{
		pthread_mutex_unlock(&rules->forks[right_id]);
		if (rules->nb_philo != 1)
			pthread_mutex_unlock(&rules->forks[left_id]);
		return (1);
	}
	pthread_mutex_lock(&rules->data_race_checker);
	philo->last_meal = get_current_timestamp();
	pthread_mutex_unlock(&rules->data_race_checker);
	print_action(rules, philo->id, "is eating");
	better_usleep(rules->time_to_eat * 1000, rules);
	return (0);
}

void	eating(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
	int	er;

	if (philo->id % 2 == 0)
		er = eating_first(philo, rules, left_id, right_id);
	else
		er = eating_second(philo, rules, left_id, right_id);
	if (er == 1)
		return ;
	pthread_mutex_lock(&rules->data_race_checker);
	philo->nb_eat++;
	if (philo->nb_eat == rules->nb_time_philo_eat)
		rules->nb_philo_eat_all++;
	pthread_mutex_unlock(&rules->data_race_checker);
	pthread_mutex_unlock(&rules->forks[left_id]);
	pthread_mutex_unlock(&rules->forks[right_id]);
}
