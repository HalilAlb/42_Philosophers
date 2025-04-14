/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:49:45 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/14 19:35:39 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_all_threads(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}


void rease_long(t_mutex *mutex, long *src)
{
    safe_mutex_handle(mutex, LOCK);
    (*src)++;
    safe_mutex_handle(mutex, UNLOCK);
}

bool all_threads_running(t_table *table)
{
    long i;
    long philo_num;

    i = -1;
    philo_num = table->philo_num;
    while(++i < philo_num)
    {
        if (table->philos[i].thread_id == 0)
            return (false);
    }
    return (true);
}
