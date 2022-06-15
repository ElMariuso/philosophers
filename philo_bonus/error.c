/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:40:10 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 15:21:52 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	leave_all_and_error(t_rules *rules, int pos, char *s)
{
	int	i;

	i = 0;
	while (i <= pos)
	{
		kill(rules->philo[i].pid, 15);
		i++;
	}
	sem_close(rules->forks);
	sem_close(rules->data_race_checker);
	sem_unlink("Forks");
	sem_unlink("Data Race");
	free_and_error(rules, s);
}

void	free_and_error(t_rules *rules, char *s)
{
	free(rules->philo);
	print_error_and_exit(s);
}

void	print_error_and_exit(char *s)
{
	printf("[ERROR]: %s\n", s);
	exit(EXIT_FAILURE);
}
