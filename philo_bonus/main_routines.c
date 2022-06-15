/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:44:14 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 16:23:38 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_anyone_dead(void *arg)
{
	int		i;
	t_rules	*rules;

	i = 0;
	rules = (t_rules *)arg;
	sem_wait(rules->death);
	sem_wait(rules->death);
	while (i != rules->nb_philo)
	{
		sem_post(rules->eat);
		i++;
	}
	i = 0;
	while (i != rules->nb_philo)
	{
		sem_post(rules->finish);
		i++;
	}
	return (NULL);
}

void	*everyone_has_eat(void	*arg)
{
	int		i;
	t_rules	*rules;

	i = 0;
	rules = (t_rules *)arg;
	while (i != rules->nb_philo)
	{
		sem_wait(rules->eat);
		i++;
	}
	i = 0;
	while (i != rules->nb_philo)
	{
		sem_wait(rules->eat);
		i++;
	}
	sem_post(rules->death);
	i = 0;
	while (i != rules->nb_philo)
	{
		sem_post(rules->finish);
		i++;
	}
	return (NULL);
}
