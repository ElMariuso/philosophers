/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:06:01 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/15 16:48:53 by mthiry           ###   ########.fr       */
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
    int nb_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_time_philo_eat;
    //forks
    //philos
} t_rules;

int     print_error(char    *message);
int     init_all(t_rules *rules, char   **argv);
int     ft_atoi(const char *str);

#endif