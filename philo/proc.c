/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:48:18 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/17 15:14:08 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *func(t_rules *rules)
{
    printf("Hey");
    while (1)
    {
        pthread_mutex_lock(&rules->forks[rules->actual]);
        printf("%d has taken a fork\n", rules->actual);
        pthread_mutex_lock(&rules->forks[(rules->actual + 1) % rules->nb_philo]);
        printf("%d has taken a fork\n", rules->actual);
        printf("%d is eating\n", rules->actual);
        usleep(rules->time_to_eat);
        pthread_mutex_unlock(&rules->forks[rules->actual]);
        pthread_mutex_unlock(&rules->forks[(rules->actual + 1) % rules->nb_philo]);
        printf("%d is sleeping\n", rules->actual);
        usleep(rules->time_to_sleep);
        printf("%d is thinking\n", rules->actual);
    }
}

int ft_proc(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        rules->actual = i;
        if (pthread_create(&rules->philo[i].thread, NULL, (void *)func, rules) != 0)
        {
            printf("Heyhey\n");
            return (1);
        }
        i++;
    }
    while (i < rules->nb_philo)
    {
        if (pthread_join(rules->philo[i].thread, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}