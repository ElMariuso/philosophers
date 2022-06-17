/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:53 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 19:08:41 by mthiry           ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long long		last_meal;
	bool			is_dead;
	struct s_rules	*rules;
	pthread_t		death_checker;
	pid_t			pid;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_philo_eat;
	long long		base_timestamp;
	bool			is_finished;
	sem_t			*forks;
	sem_t			*data_race_checker;
	sem_t			*death;
	sem_t			*eat;
	sem_t			*finish;
	pthread_t		all_death_checker;
	pthread_t		all_eat_checker;
	pthread_t		finish_checker;
	t_philo			*philo;
}	t_rules;

void		init_all(t_rules *rules, char **argv);
void		processus(t_rules *rules);
void		eating(t_philo *philo, t_rules *rules);
int			death_checker(t_rules *rules, t_philo *philo);
int			ft_atoi(const char *str);
long long	get_current_timestamp(void);
long long	time_diff(long long past, long long pres);
void		better_usleep(long long time, t_rules *rules, t_philo *philo);
void		print_action(t_rules *rules, t_philo *philo, int id, char *str);
void		leave(t_rules *rules);
void		kill_all_process(t_rules *rules);
void		close_all_semaphores(t_rules *rules);
void		print_error_and_exit(char *s);
void		free_and_error(t_rules *rules, char *s);
void		leave_all_and_error(t_rules *rules, int pos, char *s);
void		*is_anyone_dead(void *arg);
void		*everyone_has_eat(void *arg);
int			end_checker(t_rules *rules);
void		create_thread_proc(t_rules *rules, t_philo *philo);
void		destroy_thread_proc(t_rules *rules, t_philo *philo);
void		*is_finished_thread(void *arg);
void		*is_dead(void *arg);

#endif
