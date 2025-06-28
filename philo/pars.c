/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/06/29 01:15:14 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline t_bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline t_bool	ft_iswhitespace(char c)
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
		error_exit("Feed me only positive numbers");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit");
	nbr = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
		error_exit("The number is too big, INT_MAX is the limit");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The number is too big, INT_MAX is the limit");
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (av[5])
		table->num_limit_meals = ft_atol(av[5]);
	else
		table->num_limit_meals = -1;
}
