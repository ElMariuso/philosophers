/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:48:18 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/09 15:04:15 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    eating(t_philo *philo, t_rules *rules, int left_id, int right_id)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&rules->forks[left_id]);
        printf("%lld %d has taken a fork\n", get_current_timestamp(), philo->id + 1);
        pthread_mutex_lock(&rules->forks[right_id]);
        printf("%lld %d has taken a fork\n", get_current_timestamp(), philo->id + 1);
        printf("%lld %d is eating\n", get_current_timestamp(), philo->id + 1);
        usleep(rules->time_to_eat * 1000);
    }
    else
    {
        pthread_mutex_lock(&rules->forks[right_id]);
        printf("%lld %d has taken a fork\n", get_current_timestamp(), philo->id + 1);
        pthread_mutex_lock(&rules->forks[left_id]);
        printf("%lld %d has taken a fork\n", get_current_timestamp(), philo->id + 1);
        printf("%lld %d is eating\n", get_current_timestamp(), philo->id + 1);
        usleep(rules->time_to_eat * 1000);
    }
    philo->nb_eat++;
    pthread_mutex_unlock(&rules->forks[left_id]);
    pthread_mutex_unlock(&rules->forks[right_id]);
}

void    *routine(void   *arg)
{
    t_philo         *philo;
    t_rules         *rules;
    int             left_id;
    int             right_id;

    philo = (t_philo *) arg;
    rules = philo->rules;
    left_id = philo->id;
    if (philo->id == 0)
        right_id = philo->rules->nb_philo - 1;
    else
        right_id = left_id - 1;
    while (rules->someone_died == false)
    {
        if (rules->nb_philo % 2 == 0)
            eating(philo, rules, left_id, right_id);
        else
            eating(philo, rules, left_id, right_id);
        printf("%lld %d is sleeping\n", get_current_timestamp(), philo->id + 1);
        usleep(rules->time_to_sleep * 1000);
        printf("%lld %d is thinking\n", get_current_timestamp(), philo->id + 1);
    }
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