/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:37 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:21:40 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_philo	*init_thread(t_args *args, int i)
{
	t_philo	*philo;

	philo = galloc(sizeof(t_philo), args);
	mutex_allocator(&(philo->mutex), args);
	mutex_allocator(&(philo->fork), args);
	philo->is_dead = 0;
	philo->chair = i;
	philo->time_die = args->time_die;
	philo->time_eat = args->time_eat;
	philo->time_sleep = args->time_sleep;
	philo->times_eat = args->max_eats;
	if (philo->times_eat == 0)
		philo->times_eat = INT_MAX;
	philo->start_time = 0;
	philo->last_eat = 0;
	philo->next = NULL;
	philo->args = args;
	threads_allocator(philo->id, sync_philo, (void *)philo, args);
	return (philo);
}

void	args_init(t_args *args)
{
	args->l_trash = NULL;
	args->l_mutex = NULL;
	args->l_thread = NULL;
	args->philo = NULL;
	args->home = 0;
	args->any_die = 0;
	args->start_time = 0;
	mutex_allocator(&(args->mutex), args);
	mutex_allocator(&(args->sync_mutex), args);
}
