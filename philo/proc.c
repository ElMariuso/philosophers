/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:48:18 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/17 16:29:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    func(t_rules *rules)
{
    int left_id = rules->actual;
    int right_id = (rules->actual + 1) % rules->nb_philo;

    printf("Philosopher: %d\n", rules->actual);
    while (1)
    {
        break ;
        pthread_mutex_lock(&rules->forks[left_id]);
        printf("%d has taken a fork\n", rules->actual);
        pthread_mutex_lock(&rules->forks[right_id]);
        printf("%d has taken a fork\n", rules->actual);
        printf("%d is eating\n", rules->actual);
        usleep(rules->time_to_eat);
        pthread_mutex_unlock(&rules->forks[left_id]);
        pthread_mutex_unlock(&rules->forks[right_id]);
        printf("%d is sleeping\n", rules->actual);
        usleep(rules->time_to_sleep);
        printf("%d is thinking\n", rules->actual);
        break ;
    }
}

int ft_proc(t_rules *rules)
{
    int i;
    int er;

    i = 0;
    er = 0;
    while (i < rules->nb_philo)
    {
        rules->actual = i;
        er = pthread_create(rules->philo[i].thread, NULL, (void *)func, rules);
        if (er != 0)
            return (1);
        i++;
        usleep(600);
    }
    i = 0;
    while (i < rules->nb_philo)
    {
        rules->actual = i;
        er = pthread_join(*rules->philo[i].thread, NULL);
        if (er != 0)
            return (1);
        i++;
        usleep(600);
    }
    i = 0;
    while (i < rules->nb_philo)
    {
        rules->actual = i;
        er = pthread_mutex_destroy(&rules->forks[i]);
        if (er != 0)
            return (1);
        i++;
    }
    free(rules->forks);
    free(rules->philo);
    return (0);
}