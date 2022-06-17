/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:57:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 18:18:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_all_process(t_rules *rules)
{
	int	i;

	i = 0;
	while (i != rules->nb_philo)
	{
		kill(rules->philo[i].pid, 15);
		i++;
	}
}

void	close_all_semaphores(t_rules *rules)
{
	sem_close(rules->forks);
	sem_close(rules->data_race_checker);
	sem_close(rules->death);
	sem_close(rules->eat);
	sem_close(rules->finish);
	sem_unlink("Forks");
	sem_unlink("Data Race");
	sem_unlink("Death");
	sem_unlink("Eat");
	sem_unlink("Finish");
}

void	leave(t_rules *rules)
{
	int	i;
	int	ret;

	i = 0;
	while (i != rules->nb_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			kill_all_process(rules);
			break ;
		}
		i++;
	}
	close_all_semaphores(rules);
	free(rules->philo);
}
