/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:59:51 by malbayra          #+#    #+#             */
/*   Updated: 2025/03/27 17:15:08 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
    {
        error_exit("Wrong input:\n"
            "Correct is: ./philo 5 800 200 200 [5]");
    }
    else if (ac == 5 || ac == 6)
    {
        parse_input(&table, av);
    }
    
}