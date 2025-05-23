/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/05/23 15:56:46 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_iswhitespace(char c)
{
	return (((c >= 9 && c <= 13) || c == 32));
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while (ft_iswhitespace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (NULL);
	if (!ft_isdigit(*str))
		return (NULL);
	nbr = str;
	while (ft_isdigit(*str))
	{
		++len;
		++str;
	}
	if (*str != '\0')
		return (NULL);
	if (len > 10)
		return (NULL);
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long		num;
	const char	*valid;

	num = 0;
	valid = valid_input(str);
	if (!valid)
		return (-1);
	while (ft_isdigit(*valid))
		num = (num * 10) + (*valid++ - 48);
	if (num > INT_MAX)
		return (-1);
	return (num);
}

int	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	if (table->philo_num <= 0)
		return (1);
	table->time_to_die = ft_atol(av[2]) * 1000;
	if (table->time_to_die == -1)
		return (1);
	table->time_to_eat = ft_atol(av[3]) * 1000;
	if (table->time_to_eat == -1)
		return (1);
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_sleep == -1)
		return (1);
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (1);
	if (av[5])
	{
		table->num_limit_meals = ft_atol(av[5]);
		if (table->num_limit_meals == -1)
			return (1);
	}
	else
		table->num_limit_meals = -1;
	return (0);
}
