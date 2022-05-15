/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:48:05 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/14 21:48:53 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     ft_atoi(const char *str)
{
        long    res;
        int             sign;
        int             i;

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