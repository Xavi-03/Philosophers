/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:22:06 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:22:07 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->chair % 2 == 1)
	{
		pthread_mutex_lock(&(philo->fork));
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(&(philo->next->fork));
	}
	else
	{
		pthread_mutex_lock(&(philo->next->fork));
		ft_printf("has taken a fork", philo);
		pthread_mutex_lock(&(philo->fork));
	}
	ft_printf("has taken a fork", philo);
}

int	ft_eat(t_philo *philo)
{
	if (philo->args->nbr_philo > 1)
		take_forks(philo);
	else
		return (philo_alone(philo));
	ft_printf("is eating", philo);
	ft_usleep(philo->time_eat, philo);
	pthread_mutex_unlock(&(philo->next->fork));
	pthread_mutex_unlock(&(philo->fork));
	if (check_philo(philo))
		return (1);
	philo->times_eat -= 1;
	if (philo->times_eat == 0)
	{
		pthread_mutex_lock(&(philo->args->sync_mutex));
		philo->args->home += 1;
		pthread_mutex_unlock(&(philo->args->sync_mutex));
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&(philo->mutex));
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_philo(philo))
		return (1);
	ft_printf("is sleeping", philo);
	ft_usleep(philo->time_sleep, philo);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (check_philo(philo))
		return (1);
	ft_printf("is thinking", philo);
	return (0);
}

void	routine(t_philo *philo)
{
	while (!check_home(philo) && !check_philo(philo))
	{
		if (ft_eat(philo) || ft_sleep(philo) || ft_think(philo))
			return ;
	}
}
