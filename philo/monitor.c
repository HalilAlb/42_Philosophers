/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:27:31 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/14 19:29:05 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_dinner(void *data)
{
    t_table *table;
    
    table = (t_table *)data;
    
    while(!all_threads_running)
        ;

    
    return (NULL);
}