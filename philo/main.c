/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:09:52 by mthiry            #+#    #+#             */
/*   Updated: 2022/06/09 15:09:29 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    int     error_code;
    t_rules rules;

    if (argc < 5 || argc > 6)
        return (print_error("Bad number of arguments"));
    error_code = init_all(&rules, argv);
    if (error_code == 1)
        return (print_error("Something happened when initializing"));
    error_code = ft_processus(&rules);
    if (error_code == 1)
        return (print_error("Something happened when process"));
    free(rules.forks);
    free(rules.philo);
    return (0);
}