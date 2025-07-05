/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:31:51 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/05 11:43:18 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long sed)
{
	if (TAKE_FIRST_FORK == status && !simulations_fnished(philo->table))
		printf(W "%-6ld" RST "%d has taken the 1 fork 🍽️"
			"\t\t\t [🍴 %d 🍴]\n ", sed, philo->id, philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulations_fnished(philo->table))
		printf(W "%-6ld" RST "%d has taken the 2 fork 🍽️"
			"\t\t\t [🍴 %d 🍴]\n ", sed, philo->id, philo->second_fork->fork_id);
	else if (EATING == status && !simulations_fnished(philo->table))
		printf(W "%-6ld" RST "%d is eating 🍜"
			"\t\t\t [🍜 %ld 🍜]\n", sed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulations_fnished(philo->table))
		printf(W "%-6ld" RST "%d is sleeping😴\n", sed, philo->id);
	else if (THINKING == status && !simulations_fnished(philo->table))
		printf(W "%-6ld" RST "%d is thinking🤔\n", sed, philo->id);
	else if (DIAD == status)
		printf(W "%-6ld" RST "%d died😵\n", sed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, t_bool debug)
{
	long	sed;

	safe_mutex_handle(&philo->table->print_mutex, LOCK);
	sed = gettime(MILISECOND) - philo->table->start_simulation;
	if (debug)
		write_status_debug(status, philo, sed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulations_fnished(philo->table))
			printf(W "%-6ld" RST "%d has taken a fork\n", sed, philo->id);
		else if (EATING == status && !simulations_fnished(philo->table))
			printf(W "%-6ld" RST "%d is eating\n", sed, philo->id);
		else if (SLEEPING == status && !simulations_fnished(philo->table))
			printf(W "%-6ld" RST "%d is sleeping\n", sed, philo->id);
		else if (THINKING == status && !simulations_fnished(philo->table))
			printf(W "%-6ld" RST "%d is thinking\n", sed, philo->id);
		else if (DIAD == status)
			printf(W "%-6ld" RST "%d died\n", sed, philo->id);
	}
	safe_mutex_handle(&philo->table->print_mutex, UNLOCK);
}
