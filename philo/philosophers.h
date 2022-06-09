/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:06:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/09 14:54:55 by mthiry           ###   ########.fr       */
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

typedef struct s_philo
{
    int             id;
    int             nb_eat;
    struct s_rules  *rules;
    pthread_t       thread;
} t_philo;

typedef struct s_rules
{
    int             nb_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nb_time_philo_eat;
    long long       base_timestamp;
    bool            all_eat;
    bool            someone_died;
    pthread_mutex_t *forks;
    t_philo         *philo;
} t_rules;

int         print_error(char    *message);
int         init_all(t_rules *rules, char   **argv);
int         ft_processus(t_rules *rules);
int         ft_atoi(const char *str);
long long   get_current_timestamp();
int         leave(t_rules *rules);

#endif