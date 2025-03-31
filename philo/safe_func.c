/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:01:42 by malbayra          #+#    #+#             */
/*   Updated: 2025/03/27 18:05:06 by malbayra         ###   ########.fr       */
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