/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:22:01 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:22:03 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	main_errors(int n, t_args *args)
{
	if (n == 1)
		write(2, "Error:\tInvalid arguments\n\n\tValid Arguments:\n" \
			"\t\t[number_of_philosophers] [time_to_die] [time_to_eat]" \
			"[time_to_sleep]\n" \
			"\t\t[number_of_times_each_philosopher_must_eat](optional)\n", 170);
	else if (n == 2)
		write(2, "Error:\tInvalid arguments\n\n\tValid Arguments:\n" \
			"\t\t[number_of_philosophers] [time_to_die] [time_to_eat]" \
			"[time_to_sleep]\n" \
			"\t\t[number_of_times_each_philosopher_must_eat](optional)\n"
			"\n\tNumber range:\n" \
			"\t\t[number_of_philosophers]\t\t\t1\t-\t200\n"
			"\t\t[time_to_die]\t\t\t\t\t60\t-\tINT_MAX\n"
			"\t\t[time_to_eat]\t\t\t\t\t60\t-\tINT_MAX\n"
			"\t\t[time_to_sleep]\t\t\t\t\t60\t-\tINT_MAX\n"
			"\t\t[number_of_times_each_philosopher_must_eat]\t"
			"(Optional)\n", 384);
	else if (n == 3)
		write(2, "Error: Malloc failed\n", 22);
	if (args)
		free(args);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_args	*u_args;

	u_args = NULL;
	if (argc != 5 && argc != 6)
		main_errors(1, NULL);
	u_args = parser(argc, argv);
	if (!u_args)
		return (1);
	check_min_values(u_args);
	args_init(u_args);
	pthread_mutex_lock(&(u_args->sync_mutex));
	u_args->philo = threads(u_args);
	ft_usleep(5, NULL);
	u_args->start_time = get_current_time();
	pthread_mutex_unlock(&(u_args->sync_mutex));
	monitoring(u_args);
	terminate(u_args);
	printf("programa finalizado\n");
	return (0);
}
