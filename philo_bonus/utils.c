/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:06:53 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/15 15:59:37 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (res * sign < INT_MIN)
			return (0);
		else if (res > INT_MAX)
			return (-1);
	}
	return (res * sign);
}

long long	get_current_timestamp(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (ms);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	better_usleep(long long time, t_rules *rules, t_philo *philo)
{
	long long	i;

	i = get_current_timestamp();
	while (time_diff(i, get_current_timestamp()) * 1000 < time)
	{
		if (death_checker(rules, philo) == 1)
			break ;
		usleep(500);
	}
}

void	print_action(t_rules *rules, t_philo *philo, int id, char *str)
{
	long long	time;

	sem_wait(rules->data_race_checker);
	time = time_diff(rules->base_timestamp, get_current_timestamp());
	if (philo->is_dead == false && rules->is_finished == false)
		printf("%lld %d %s\n", time, id + 1, str);
	sem_post(rules->data_race_checker);
}
