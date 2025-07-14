/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:54:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/14 19:52:54 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_num;

	philo_num = philo->table->philo_num;
	philo->first_fork = &forks[(philo_position + 1) % philo_num];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_num];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = FALSE;
		philo->meals_counter = 0;
		philo->table = table;
		if (safe_mutex_handle(&philo->philo_mutex, INIT) != 0)
			return (1);
		assign_fork(philo, table->forks, i);
	}
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = FALSE;
	table->all_threads_ready = FALSE;
	table->error_occurred = FALSE;
	table->threads_running_num = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_num);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_num);
	if (safe_mutex_handle(&table->table_mutex, INIT) != 0)
		return (1);
	if (safe_mutex_handle(&table->print_mutex, INIT) != 0)
		return (1);
	while (++i < table->philo_num)
	{
		if (safe_mutex_handle(&table->forks[i].fork, INIT) != 0)
			return (1);
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) != 0)
		return (1);
	return (0);
}
