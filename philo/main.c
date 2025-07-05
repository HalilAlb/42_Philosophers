/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:59:51 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/05 11:43:53 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		error_exit("Wrong input:\n"
			"Correct is: ./philo 5 800 200 200 [5]");
	}
	if (parse_input(&table, av) != 0)
	{
		return (1);
	}
	if (data_init(&table) != 0)
	{
		clean(&table); 
		return (1);
	}
	dinner_start(&table);
	clean(&table);
	return (0);
}
