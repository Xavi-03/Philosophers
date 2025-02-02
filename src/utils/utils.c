/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:22:18 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:22:19 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	philo_alone(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	ft_printf("has taken a fork", philo);
	while (!check_philo(philo))
		ft_usleep(1, philo);
	return (1);
}

int	check_monitoring(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex));
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&(philo->mutex));
		pthread_mutex_lock(&(philo->args->mutex));
		philo->args->any_die = 1;
		pthread_mutex_unlock(&(philo->args->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->mutex));
	return (0);
}

int	check_home(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->sync_mutex));
	if (philo->args->home == philo->args->nbr_philo)
	{
		pthread_mutex_unlock(&(philo->args->sync_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->args->sync_mutex));
	return (0);
}

int	check_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex));
	pthread_mutex_lock(&(philo->args->mutex));
	if ((get_current_time() - philo->last_eat) > (unsigned long)philo->time_die
		|| philo->args->any_die)
	{
		pthread_mutex_unlock(&(philo->args->mutex));
		philo->is_dead = 1;
		pthread_mutex_unlock(&(philo->mutex));
		return (1);
	}
	if (philo->args->any_die)
	{
		pthread_mutex_unlock(&(philo->args->mutex));
		pthread_mutex_unlock(&(philo->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->args->mutex));
	pthread_mutex_unlock(&(philo->mutex));
	return (0);
}

void	ft_printf(char *text, t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->sync_mutex));
	if (check_philo(philo))
	{
		pthread_mutex_unlock(&(philo->args->sync_mutex));
		return ;
	}
	printf("%zu %i %s\n", (get_current_time() - philo->start_time),
		philo->chair + 1, text);
	pthread_mutex_unlock(&(philo->args->sync_mutex));
}
