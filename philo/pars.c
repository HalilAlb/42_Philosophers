/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:12:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/07/07 18:04:41 by malbayra         ###   ########.fr       */
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
		return (error_exit("Feed me only positive numbers"), NULL);
	if (!ft_isdigit(*str))
		return (error_exit("The input is not a correct digit"), NULL);
	nbr = str;
	while (ft_isdigit(*str))
	{
		++len;
		++str;
	}
	if (*str != '\0')
		return (error_exit("invalid input"), NULL);
	if (len > 10)
		return (error_exit("The number is too big, INT_MAX is the limit"),
			NULL);
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (0);
	while (ft_isdigit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		return (error_exit("The number is too big, INT_MAX is the limit"), 0);
	return (num);
}

int	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	if (table->philo_num == 0)
		return (1);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	if (table->time_to_die == 0)
		return (1);
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	if (table->time_to_eat == 0)
		return (1);
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_sleep == 0)
		return (1);
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (error_exit("Use timestamps major than 60ms"), 1);
	if (av[5])
	{
		table->num_limit_meals = ft_atol(av[5]);
		if (table->num_limit_meals == 0)
			return (1);
	}
	else
		table->num_limit_meals = -1;
	return (0);
}
