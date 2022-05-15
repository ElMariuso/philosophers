/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:09:52 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/15 16:46:41 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_rules rules;

    if (argc < 5 || argc > 6)
        return (print_error("Bad number of arguments"));
    init_all(&rules, argv);
    return (0);
}