/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:55:49 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 15:03:16 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_rules *rules)
{
	pthread_mutex_lock(&rules->data_race_checker);
	if (rules->someone_died == true)
	{
		pthread_mutex_unlock(&rules->data_race_checker);
		return (1);
	}
	pthread_mutex_unlock(&rules->data_race_checker);
	return (0);
}

int	eat_checker(t_rules *rules)
{
	pthread_mutex_lock(&rules->data_race_checker);
	if (rules->nb_philo_eat_all == rules->nb_philo)
	{
		pthread_mutex_unlock(&rules->data_race_checker);
		return (1);
	}
	pthread_mutex_unlock(&rules->data_race_checker);
	return (0);
}
