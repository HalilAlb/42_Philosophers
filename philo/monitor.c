/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:27:31 by malbayra          #+#    #+#             */
/*   Updated: 2025/06/29 01:16:52 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_dead(t_philo *philo)
{
	long	sed;
	long	to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (FALSE);
	sed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	to_die = philo->table->time_to_die / 1e3;
	if (sed > to_die)
		return (TRUE);
	return (FALSE);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_num, table->philo_num))
		;
	while (!simulations_fnished(table))
	{
		i = -1;
		while (++i < table->philo_num && !simulations_fnished(table))
		{
			if (philo_dead(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, TRUE);
				write_status(DIAD, table->philos + i, DEBUG_MOD);
			}
		}
	}
	return (NULL);
}
