/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:08:52 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 16:01:10 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sem_open_first(t_rules *rules)
{
	rules->forks = sem_open("Forks", O_CREAT, S_IRUSR, rules->nb_philo);
	if (rules->forks == SEM_FAILED)
		free_and_error(rules, "Something happened when initializing semaphore");
	rules->data_race_checker = sem_open("Data Race", O_CREAT, S_IRUSR, 1);
	if (rules->data_race_checker == SEM_FAILED)
	{
		sem_unlink("Forks");
		sem_close(rules->forks);
		free_and_error(rules, "Something happened when initializing semaphore");
	}
}

void	sem_open_second(t_rules *rules)
{
	rules->death = sem_open("Death", O_CREAT, S_IRUSR, 1);
	if (rules->death == SEM_FAILED)
	{
		sem_unlink("Forks");
		sem_unlink("Data Race");
		sem_close(rules->forks);
		sem_close(rules->data_race_checker);
		free_and_error(rules, "Something happened when initializing semaphore");
	}
	rules->eat = sem_open("Eat", O_CREAT, S_IRUSR, rules->nb_philo);
	if (rules->eat == SEM_FAILED)
	{
		sem_unlink("Forks");
		sem_unlink("Data Race");
		sem_unlink("Death");
		sem_close(rules->forks);
		sem_close(rules->data_race_checker);
		sem_close(rules->death);
		free_and_error(rules, "Something happened when initializing semaphore");
	}
}

void	init_semaphore(t_rules *rules)
{
	sem_unlink("Forks");
	sem_unlink("Data Race");
	sem_unlink("Death");
	sem_unlink("Eat");
	sem_unlink("Finish");
	sem_open_first(rules);
	sem_open_second(rules);
	rules->finish = sem_open("Finish", O_CREAT, S_IRUSR, rules->nb_philo);
	if (rules->data_race_checker == SEM_FAILED)
	{
		sem_unlink("Forks");
		sem_unlink("Data Race");
		sem_unlink("Death");
		sem_unlink("Eat");
		sem_close(rules->forks);
		sem_close(rules->data_race_checker);
		sem_close(rules->death);
		sem_close(rules->eat);
		free_and_error(rules, "Something happened when initializing semaphore");
	}
}

void	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philo = (t_philo *) malloc (rules->nb_philo * sizeof(t_philo));
	if (!rules->philo)
		print_error_and_exit(
			"Something happened when initializing philosophers");
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].nb_eat = 0;
		rules->philo[i].last_meal = rules->base_timestamp;
		rules->philo[i].rules = rules;
		rules->philo[i].is_dead = false;
		i++;
	}
}

void	init_all(t_rules *rules, char **argv)
{
	rules->base_timestamp = get_current_timestamp();
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (rules->nb_philo <= 0 || rules->nb_philo > INT_MAX
		|| rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
		print_error_and_exit("Wrong arguments");
	if (argv[5] != NULL)
	{
		rules->nb_time_philo_eat = ft_atoi(argv[5]);
		if (rules->nb_time_philo_eat <= 0)
			print_error_and_exit("Wrong arguments");
	}
	else
		rules->nb_time_philo_eat = -1;
	rules->is_finished = false;
	init_philos(rules);
	init_semaphore(rules);
}
