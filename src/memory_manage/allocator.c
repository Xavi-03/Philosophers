/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:29 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:21:34 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	init_galloc(t_args *args)
{
	args->l_trash = malloc(sizeof(t_trash));
	if (!args->l_trash)
		exit(1);
	args->l_trash->mem = NULL;
	args->l_trash->start = args->l_trash;
}

void	*galloc(size_t size, t_args *args)
{
	t_trash			*new_node;
	void			*mem;

	new_node = NULL;
	if (!args->l_trash)
		init_galloc(args);
	mem = malloc(size);
	if (!mem)
		terminate(args);
	new_node = malloc(sizeof(t_trash));
	if (!new_node)
	{
		free(mem);
		terminate(args);
	}
	new_node->mem = mem;
	args->l_trash->next = new_node;
	new_node->start = args->l_trash->start;
	args->l_trash = new_node;
	args->l_trash->next = NULL;
	return (mem);
}

void	mutex_allocator(pthread_mutex_t *mutex, t_args *args)
{
	t_mutex	*new_node;

	new_node = NULL;
	if (!args->l_mutex)
	{
		args->l_mutex = galloc(sizeof(t_mutex), args);
		if (!args->l_mutex)
			terminate(args);
		args->l_mutex->flag = 0;
		args->l_mutex->next = NULL;
		args->l_mutex->start = args->l_mutex;
	}
	new_node = galloc(sizeof(t_mutex), args);
	if (!new_node)
		terminate(args);
	if (pthread_mutex_init(&(*mutex), NULL))
		terminate(args);
	new_node->mutex = *mutex;
	args->l_mutex->next = new_node;
	new_node->start = args->l_mutex->start;
	args->l_mutex = new_node;
	args->l_mutex->flag = 1;
	args->l_mutex->next = NULL;
}

void	threads_allocator(pthread_t id, void *func, void *param, t_args *args)
{
	t_thread		*new_node;

	new_node = NULL;
	if (!args->l_thread)
	{
		args->l_thread = galloc(sizeof(t_thread), args);
		if (!args->l_thread)
			terminate(args);
		args->l_thread->flag = 0;
		args->l_thread->start = args->l_thread;
	}
	new_node = galloc(sizeof(t_thread), args);
	if (!new_node)
		terminate(args);
	if (pthread_create(&id, NULL, func, param))
		terminate (args);
	new_node->id = id;
	args->l_thread->next = new_node;
	new_node->start = args->l_thread->start;
	args->l_thread = new_node;
	args->l_thread->flag = 1;
	args->l_thread->next = NULL;
	return ;
}
