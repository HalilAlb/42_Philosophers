/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:54:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/07 17:43:00 by malbayra         ###   ########.fr       */
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

static void	philo_init(t_table *table)
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
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_fork(philo, table->forks, i);
	}
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = FALSE;
	table->all_threads_ready = FALSE;
	table->threads_running_num = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_num);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_num);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->print_mutex, INIT);
	while (++i < table->philo_num)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (0);
}
