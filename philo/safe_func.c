/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:01:42 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/01 14:41:56 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *safe_malloc(size_t bytes)
{
    void *ptr;

    ptr = malloc(bytes);
    if (NULL == ptr)
        error_exit("Malloc failed");
    return (ptr);
}

void safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
    if(LOCK == opcode)
        pthread_mutex_lock(mutex);
    else if(UNLOCK == opcode)
        pthread_mutex_unlock(mutex);
    else if(INIT == opcode)
        pthread_mutex_init(mutex, NULL);
    else if(DESTROY == opcode)
        pthread_mutex_destroy(mutex);
    else
        error_exit("wrong opcode for mutex handle");
}