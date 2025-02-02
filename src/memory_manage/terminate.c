/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:43 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:21:46 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	terminate(t_args *args)
{
	thread_destroyer(args);
	mutex_destroyer(args);
	free_galloc(args);
	free(args);
	exit(42);
}

void	thread_destroyer(t_args *args)
{
	t_thread	*temp_thread;

	temp_thread = args->l_thread->start;
	while (temp_thread)
	{
		if (temp_thread->flag)
			pthread_join(temp_thread->id, NULL);
		temp_thread = temp_thread->next;
	}
}

void	mutex_destroyer(t_args *args)
{
	t_mutex	*temp_mutex;

	temp_mutex = args->l_mutex->start;
	while (temp_mutex)
	{
		if (temp_mutex->flag)
			pthread_mutex_destroy(&(temp_mutex->mutex));
		temp_mutex = temp_mutex->next;
	}
}

void	free_galloc(t_args *args)
{
	t_trash	*trash;
	t_trash	*temp_trash;

	trash = args->l_trash->start;
	while (trash)
	{
		temp_trash = trash;
		trash = trash->next;
		if (temp_trash->mem != NULL)
			free(temp_trash->mem);
		free(temp_trash);
	}
}
