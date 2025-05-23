/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:59:51 by malbayra          #+#    #+#             */
/*   Updated: 2025/05/23 14:24:44 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong input:\nCorrect is: ./philo 5 800 200 200 [5]\n");
		return (1);
	}
	if (parse_input(&table, av) != 0)
	{
		printf("Error: Invalid input parameters\n");
		return (1);
	}
	if (data_init(&table) != 0)
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (dinner_start(&table) != 0)
	{
		clean(&table);
		return (1);
	}
	clean(&table);
	return (0);
}
