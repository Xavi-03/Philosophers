/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:22:10 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:22:12 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*sync_philo(void *param)
{
	pthread_mutex_lock(&(((t_philo *)param)->args->sync_mutex));
	((t_philo *)param)->start_time = ((t_philo *)param)->args->start_time;
	((t_philo *)param)->last_eat = ((t_philo *)param)->args->start_time;
	pthread_mutex_unlock(&(((t_philo *)param)->args->sync_mutex));
	if (((t_philo *)param)->chair % 2 == 1)
		ft_usleep(30, NULL);
	routine(param);
	return (NULL);
}

t_philo	*threads(t_args *args)
{
	int		i;
	t_philo	*first_philo;
	t_philo	*temp_philo;

	i = 0;
	first_philo = init_thread(args, i);
	temp_philo = first_philo;
	while (++i < args->nbr_philo)
	{
		temp_philo->next = init_thread(args, i);
		temp_philo = temp_philo->next;
	}
	temp_philo->next = first_philo;
	return (first_philo);
}
