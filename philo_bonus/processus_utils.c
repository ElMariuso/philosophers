/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:57:56 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 16:25:09 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_rules *rules, t_philo *philo)
{
	sem_wait(rules->data_race_checker);
	if (philo->is_dead == true)
	{
		sem_post(rules->data_race_checker);
		return (1);
	}
	sem_post(rules->data_race_checker);
	return (0);
}

int	end_checker(t_rules *rules)
{
	sem_wait(rules->data_race_checker);
	if (rules->is_finished == true)
	{
		sem_post(rules->data_race_checker);
		return (1);
	}
	sem_post(rules->data_race_checker);
	return (0);
}

void	create_thread_proc(t_rules *rules, t_philo *philo)
{
	int	er;

	er = 0;
	er = pthread_create(&rules->finish_checker, NULL,
			(void *)is_finished_thread, (void *)rules);
	if (er != 0)
		exit(EXIT_FAILURE);
	er = pthread_create(&philo->death_checker, NULL,
			(void *)is_dead, (void *)philo);
	if (er != 0)
	{
		er = pthread_join(rules->finish_checker, NULL);
		if (er != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}

void	destroy_thread_proc(t_rules *rules, t_philo *philo)
{
	int	er;

	er = 0;
	er = pthread_join(philo->death_checker, NULL);
	if (er != 0)
	{
		er = pthread_join(rules->finish_checker, NULL);
		if (er != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	pthread_join(rules->finish_checker, NULL);
	if (er != 0)
		exit(EXIT_FAILURE);
}
