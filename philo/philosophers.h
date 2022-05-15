/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:06:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/15 20:25:51 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_rules
{
    int     nb_philo;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     nb_time_philo_eat;
    bool    all_eat;
    //forks
    //philos
} t_rules;

typedef struct s_philo
{
    int         id;
    int         nb_eat;
    int         right_fork;
    int         left_fork;
    t_rules     rules;
    pthread_t   thread;
} t_philo;

int     print_error(char    *message);
int     init_all(t_rules *rules, char   **argv);
int     ft_atoi(const char *str);

#endif