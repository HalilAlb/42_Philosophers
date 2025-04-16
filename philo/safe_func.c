/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:01:42 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/17 00:45:06 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (NULL == ptr)
		error_exit("Malloc failed");
	return (ptr);
}

static void	handle_mutex_error(int stat, t_opcode opcode)
{
	if (0 == stat)
		return ;
	if (EINVAL == stat && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value of the mutex is invalid");
	else if (EINVAL == stat && INIT == opcode)
		error_exit("The value of the mutex is invalid");
	else if (EDEADLK == stat)
		error_exit("A deadlock would accur if the thread\
			blocked waiting for the mutex");
	else if (EPERM == stat)
		error_exit("The current thread does not hold a lock on mutex");
	else if (ENOMEM == stat)
		error_exit("The process connot allocate enough\
			memory to create another the mutex");
	else if (EBUSY == stat)
		error_exit("Mutex is Locked");
}

void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong opcode for mutex handle");
}

static void	handle_thread_error(int stat, t_opcode opcode)
{
	if (0 == stat)
		return ;
	if (EAGAIN == stat)
		error_exit("No resources to create another thread");
	else if (EPERM == stat)
		error_exit("The caller dose not have appropriate permission");
	else if (EINVAL == stat && CREATE == opcode)
		error_exit("The value specified by threads is not joinable\n");
	else if (EINVAL == stat && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by threads is not joinable\n");
	else if (ESRCH == stat)
		error_exit("No thread could be found corresponding to that"
			" specified by the given thread ID, thread.");
	else if (EDEADLK == stat)
		error_exit("A deadlock was detected or the value of"
			" thread specifies the calling thread");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit(" Wrong opcode for thread handle:"
			" use <CREATE> <JOIN> <DETACH>");
}
