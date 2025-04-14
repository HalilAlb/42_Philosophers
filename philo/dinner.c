/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:35:10 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/14 17:08:48 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinner_simulations(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    while (!simulations_fnished(philo->table))
    {
       
    }

    return (NULL);  
}

void dinner_start(t_table *table)
{
    int i;
    
    i = -1;
    if (0 == table->num_limit_meals)
        return ;
    else if (1 == table->philo_num)
        ;
    else
    {
        while (i++ < table->philo_num)
            safe_thread_handle(&table->philos[i].thread_id,dinner_simulations,
                &table->philos[i], CREATE);
    }
    table->start_simulation = gettime(MILISECOND);    
    set_bool(&table->table_mutex, &table->all_threads_ready, true);

    i = -1;
    while (++i < table->philo_num)
        safe_thread_handle(&table->philos[i].thread_id,NULL,NULL, JOIN);
}