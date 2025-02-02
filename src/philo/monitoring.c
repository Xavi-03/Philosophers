/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:58 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:21:59 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	monitoring_philo_is_dead(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->mutex));
	args->any_die = 1;
	pthread_mutex_unlock(&(philo->args->mutex));
	printf("%zu %i died\n", get_current_time()
		- philo->start_time, philo->chair + 1);
	ft_usleep(5000, NULL);
}

void	monitoring(t_args *args)
{
	t_philo	*philo;
	int		i;

	ft_usleep(20, NULL);
	philo = args->philo;
	pthread_mutex_lock(&(args->sync_mutex));
	while (args->home < args->nbr_philo)
	{
		pthread_mutex_unlock(&(args->sync_mutex));
		philo = args->philo;
		i = 0;
		while (i < args->nbr_philo)
		{
			if (check_monitoring(philo))
			{
				monitoring_philo_is_dead(args, philo);
				return ;
			}
			philo = philo->next;
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&(args->sync_mutex));
	}
	pthread_mutex_unlock(&(args->sync_mutex));
}
