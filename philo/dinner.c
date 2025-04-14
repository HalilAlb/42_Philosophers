/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:35:10 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/14 19:34:19 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MOD);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MOD);
}

static void eat(t_philo *philo)
{
  safe_mutex_handle(&philo->first_fork->fork, LOCK);
  write_status(TAKE_FIRST_FORK, philo, DEBUG_MOD);
  safe_mutex_handle(&philo->second_fork->fork, LOCK);
  write_status(TAKE_SECOND_FORK, philo, DEBUG_MOD);

  set_long(&philo->philo_mutex, &philo->last_meal_time,gettime(MILISECOND));
  philo->meals_counter++;
  write_status(EATING, philo, DEBUG_MOD);
  precise_usleep(philo->table->time_to_eat, philo->table);
  if (philo->table->num_limit_meals > 0 && 
    philo->meals_counter >= philo->table->num_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
     safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
     safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}


void *dinner_simulations(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    rease_long(&philo->table->table_mutex, 
        &philo->table->threads_running_num);
    
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
    safe_thread_handle(&table->monitor_thread,monitor_dinner,table,CREATE);
    table->start_simulation = gettime(MILISECOND);    
    set_bool(&table->table_mutex, &table->all_threads_ready, true);

    i = -1;
    while (++i < table->philo_num)
        safe_thread_handle(&table->philos[i].thread_id,NULL,NULL, JOIN);
}