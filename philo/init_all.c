/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:57:47 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/09 14:54:48 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_forks(t_rules *rules)
{
    int i;

    i = 0;
    rules->forks = (pthread_mutex_t *) malloc (rules->nb_philo * sizeof(pthread_mutex_t));
    if (!rules->forks)
        return (1);
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL))
            return (1);
        i++;
    }
    return (0);
}

int init_philos(t_rules *rules)
{
    int i;

    i = 0;
    rules->philo = (t_philo *) malloc (rules->nb_philo * sizeof(t_philo));
    if (!rules->philo)
        return (1);
    while (i < rules->nb_philo)
    {
        rules->philo[i].id = i;
        rules->philo[i].nb_eat = 0;
        rules->philo[i].rules = rules;
        i++;
    }
    return (0);
}

int init_all(t_rules *rules, char   **argv)
{
    rules->base_timestamp = get_current_timestamp();
    rules->nb_philo = ft_atoi(argv[1]);
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);
    if (rules->nb_philo <= 0 || rules->nb_philo > INT_MAX || rules->time_to_die <= 0 
    || rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
        return (1);
    if (argv[5] != NULL)
    {
        rules->nb_time_philo_eat = ft_atoi(argv[5]);
        if (rules->nb_time_philo_eat <= 0)
            return (1);
    }
    else
        rules->nb_time_philo_eat = 0;
    rules->all_eat = false;
    rules->someone_died = false;
    if (init_forks(rules) != 0)
        return (1);
    if (init_philos(rules) != 0)
        return (1);
    return (0);
}