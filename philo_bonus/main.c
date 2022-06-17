/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:55:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 19:05:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_thread(t_rules rules)
{
	int	er;

	er = 0;
	er = pthread_create(&rules.all_death_checker, NULL,
			(void *)is_anyone_dead, (void *)&rules);
	if (er != 0)
	{
		leave(&rules);
		exit(EXIT_FAILURE);
	}
	er = pthread_create(&rules.all_eat_checker, NULL,
			(void *)everyone_has_eat, (void *)&rules);
	if (er != 0)
	{
		er = pthread_join(rules.all_death_checker, NULL);
		if (er != 0)
		{
			leave(&rules);
			exit(EXIT_FAILURE);
		}
		leave(&rules);
		exit(EXIT_FAILURE);
	}
}

void	destroy_thread(t_rules rules)
{
	int	er;

	er = 0;
	er = pthread_join(rules.all_death_checker, NULL);
	if (er != 0)
	{
		er = pthread_join(rules.all_eat_checker, NULL);
		if (er != 0)
		{
			leave(&rules);
			exit(EXIT_FAILURE);
		}
		leave(&rules);
		exit(EXIT_FAILURE);
	}
	er = pthread_join(rules.all_eat_checker, NULL);
	if (er != 0)
	{
		leave(&rules);
		exit(EXIT_FAILURE);
	}
}

void	lock_finisher(t_rules *rules)
{
	int	i;

	i = 0;
	while (i != rules->nb_philo)
	{
		sem_wait(rules->finish);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		print_error_and_exit("Bad number of arguments");
	rules.base_timestamp = get_current_timestamp();
	init_all(&rules, argv);
	lock_finisher(&rules);
	processus(&rules);
	create_thread(rules);
	destroy_thread(rules);
	leave(&rules);
	exit(EXIT_SUCCESS);
	return (0);
}
