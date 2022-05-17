/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:09:52 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/17 15:12:59 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    int     error_code;
    t_rules rules;

    if (argc < 5 || argc > 6)
        return (print_error("Bad number of arguments\n"));
    error_code = init_all(&rules, argv);
    if (error_code == 1)
        return (print_error("Something happened when initializing\n"));
    error_code = ft_proc(&rules);
    if (error_code == 1)
        return (print_error("Something happened when process\n"));
    return (0);
}