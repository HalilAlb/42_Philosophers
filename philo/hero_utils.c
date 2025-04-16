/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:49:45 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/17 00:40:51 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

void	rease_long(t_mutex *mutex, long *src)
{
	safe_mutex_handle(mutex, LOCK);
	(*src)++;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	all_threads_running(t_mutex *mutex, long *threads, long philo_num)
{
	bool	res;

	res = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_num)
		res = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	sync_philo(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
