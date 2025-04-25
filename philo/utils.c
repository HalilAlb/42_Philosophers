/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:02:39 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/25 15:04:22 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong input to gettime");
	return (1337);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	sed;
	long	rum;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulations_fnished(table))
			break ;
		sed = gettime(MICROSECOND);
		rum = usec - sed;
		if (rum > 1e3)
			usleep(rum / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error_message)
{
	printf("Error: %s\n", error_message);
	exit(EXIT_FAILURE);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->print_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
