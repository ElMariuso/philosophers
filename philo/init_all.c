/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:57:47 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/15 20:26:07 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_all(t_rules *rules, char   **argv)
{
    rules->nb_philo = ft_atoi(argv[1]);
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);
    if (rules->nb_philo <= 0 || rules->time_to_die <= 0 
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
    return (0);
}