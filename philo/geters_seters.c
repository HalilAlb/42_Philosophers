/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters_seters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:40:56 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/17 00:41:14 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *src)
{
	bool	value;

	safe_mutex_handle(mutex, LOCK);
	value = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}

long	get_long(t_mutex *mutex, long *src)
{
	long	value;

	safe_mutex_handle(mutex, LOCK);
	value = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulations_fnished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
