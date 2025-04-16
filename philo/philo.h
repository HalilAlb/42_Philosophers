/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:44:08 by malbayra          #+#    #+#             */
/*   Updated: 2025/04/16 14:13:45 by malbayra         ###   ########.fr       */
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
# include <errno.h>


#define DEBUG_MOD 0

#endif

typedef enum s_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIAD,
} t_philo_status;

typedef enum e_opcode
{
   LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}  t_opcode;

typedef enum e_time_code
{
    SECOND,
    MILISECOND,
    MICROSECOND,
} t_time_code;

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
    t_fork  *first_fork;
    t_fork  *second_fork;
    pthread_t   thread_id;
    t_mutex     philo_mutex;
    t_table     *table;
}               t_philo;

typedef struct s_table
{
    long philo_num;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long num_limit_meals;
    long start_simulation;
    bool all_threads_ready;
    bool end_simulation;
    long threads_running_num;
    pthread_t monitor_thread;
    t_mutex table_mutex;
    t_mutex print_mutex;
    t_fork *forks;
    t_philo *philos;
}              t_table;


void error_exit(char *error_message);
void parse_input(t_table *table, char **av);
void *safe_malloc(size_t bytes);
void data_init(t_table *table);
void safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
    void *data,t_opcode opcode);
void set_bool(t_mutex *mutex, bool *dest, bool value);
bool get_bool(t_mutex *mutex, long *src);
long get_long(t_mutex *mutex, long *src);
void set_long(t_mutex *mutex, long *dest, long value);
bool simulations_fnished(t_table *table);
long gettime(t_time_code time_code);

bool all_threads_running(t_mutex *mutex, long *threads,long philo_num);

void wait_all_threads(t_table *table);
void precise_usleep(long usec, t_table *table);
void *monitor_dinner(void *data);
void thinking(t_philo *philo, bool pre_smilutaion);



void write_status(t_philo_status status, t_philo *philo, bool debug);





