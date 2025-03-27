/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:44:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/03/27 17:43:16 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

#endif

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
    t_mutex     fork;
    int     fork_id;
}           t_fork;

typedef struct s_philo
{
    int     id;
    long    meals_counter;
    bool    full;
    long    last_meal_time;
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t   thread_id;
    t_table     *table;
}               t_philo;

typedef struct s_table
{
    long philo_num;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long num_limit_meals;
    long start_time;
    bool end_simulation;
    t_fork *forks;
    t_philo *philos;
}              t_table;


void error_exit(char *error_message);
void parse_input(t_table *table, char **av);

