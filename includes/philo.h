/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:23:02 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:23:05 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_args
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	sync_mutex;
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eats;
	int				home;
	int				any_die;
	size_t			start_time;
	struct s_philo	*philo;
	struct s_trash	*l_trash;
	struct s_mutex	*l_mutex;
	struct s_thread	*l_thread;
}	t_args;

typedef struct s_philo
{
	pthread_t		id;
	pthread_mutex_t	mutex;
	pthread_mutex_t	fork;
	int				is_dead;
	int				chair;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	size_t			start_time;
	size_t			last_eat;
	struct s_philo	*next;
	struct s_args	*args;
}	t_philo;

typedef struct s_trash
{
	void			*mem;
	struct s_trash	*next;
	struct s_trash	*start;
}			t_trash;

typedef struct s_thread
{
	pthread_t			id;
	int					flag;
	struct s_thread		*next;
	struct s_thread		*start;
}			t_thread;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				flag;
	struct s_mutex	*next;
	struct s_mutex	*start;
}			t_mutex;

//memory_manage
//	allocator.c
void			*galloc(size_t size, t_args *args);
void			mutex_allocator(pthread_mutex_t *mutex, t_args *args);
void			threads_allocator(pthread_t id, void *func, void *param,
					t_args *args);
//	init.c
t_philo			*init_thread(t_args *args, int i);
void			args_init(t_args *args);
//	terminate.c
void			terminate(t_args *args);
void			thread_destroyer(t_args *args);
void			mutex_destroyer(t_args *args);
void			free_galloc(t_args *args);
//parser
//	parser.c
unsigned int	ft_atou(char *str, int *error);
t_args			*parser( int argc, char **argv);
void			check_min_values(t_args *args);
//	parser_utils.c
int				ft_isdigit(char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
//philo
//	monitoring.c
void			monitoring(t_args *args);
//	philo.c
void			main_errors(int n, t_args *args);
//	routine.c
int				ft_eat(t_philo *philo);
int				ft_sleep(t_philo *philo);
int				ft_think(t_philo *philo);
void			routine(t_philo *philo);
//threads
//	threads.c
void			*sync_philo(void *param);
t_philo			*create_threads(t_args *args, int i);
t_philo			*threads(t_args *args);
//utils
//	time.c
size_t			get_current_time(void);
int				ft_usleep(size_t milliseconds, t_philo *philo);
//	utils.c
int				philo_alone(t_philo *philo);
int				check_monitoring(t_philo *philo);
int				check_home(t_philo *philo);
int				check_philo(t_philo *philo);
void			ft_printf(char *text, t_philo *philo);

#endif
