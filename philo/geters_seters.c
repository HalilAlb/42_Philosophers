/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters_seters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:40:56 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/02 22:47:22 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mutex, t_bool *dest, t_bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

t_bool	get_bool(t_mutex *mutex, t_bool *src)
{
	t_bool	value;

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

t_bool	simulations_fnished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
