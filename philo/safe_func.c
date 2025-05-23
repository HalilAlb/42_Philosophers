/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:01:42 by malbayra          #+#    #+#             */
/*   Updated: 2025/05/23 14:27:09 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (NULL == ptr)
		return (NULL);
	return (ptr);
}

static int	handle_mutex_error(int stat, t_opcode opcode)
{
	if (0 == stat)
		return (0);
	if (EINVAL == stat && (LOCK == opcode || UNLOCK == opcode
			|| DESTROY == opcode))
		return (1);
	else if (EINVAL == stat && INIT == opcode)
		return (1);
	else if (EDEADLK == stat)
		return (1);
	else if (EPERM == stat)
		return (1);
	else if (ENOMEM == stat)
		return (1);
	else if (EBUSY == stat)
		return (1);
	return (1);
}

int	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	int	result;

	if (LOCK == opcode)
		result = handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		result = handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		result = handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		result = handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		return (1);
	return (result);
}

static int	handle_thread_error(int stat, t_opcode opcode)
{
	(void)opcode;
	if (0 == stat)
		return (0);
	if (EAGAIN == stat || EPERM == stat || EINVAL == stat || ESRCH == stat
		|| EDEADLK == stat)
		return (1);
	return (1);
}

int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	int	result;

	if (CREATE == opcode)
		result = handle_thread_error(pthread_create(thread, NULL, foo, data),
				opcode);
	else if (JOIN == opcode)
		result = handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		result = handle_thread_error(pthread_detach(*thread), opcode);
	else
		return (1);
	return (result);
}
