/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:48:18 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/17 17:51:54 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    eating(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
    pthread_mutex_lock(&rules->forks[left_id]);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_lock(&rules->forks[right_id]);
    printf("%d has taken a fork\n", philo->id);
    printf("%d is eating\n", philo->id);
    usleep(rules->time_to_eat);
    pthread_mutex_unlock(&rules->forks[left_id]);
    pthread_mutex_unlock(&rules->forks[right_id]);
}

void    *routine(t_philo    philo)
{
    (void)philo;
    int i = philo.id;
    printf("%d\n", i);
    return (NULL);
}

int ft_processus(t_rules *rules)
{
    int i;
    int er;

    i = 0;
    er = 0;
    while (i < rules->nb_philo)
    {
        printf("philo: %d\n", rules->philo[i].id);
        er = pthread_create(&rules->philo[i].thread, NULL, (void *)routine, (void *)&rules->philo[i]);
        if (er != 0)
            return (1);
        i++;
    }
    er = leave(rules);
    if (er == 1)
        return (1);
    return (0);
}