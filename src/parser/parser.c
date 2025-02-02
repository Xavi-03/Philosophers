/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:49 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/01/20 20:21:51 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static unsigned int	check_int(unsigned int nbr, char *str, int *error, int i)
{
	if (i == 10)
	{
		if (ft_strncmp("2147483647", str, 11) >= 0)
			return (nbr);
		*error = 1;
	}
	else if (i > 10)
	{
		*error = 1;
		return (0);
	}
	return (nbr);
}

unsigned int	ft_atou(char *str, int *error)
{
	int				i;
	unsigned int	nbr;

	i = -1;
	nbr = 0;
	if (str[0] == '+')
		str++;
	while (str[0] == '0' && str[1] != '\0')
		str++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			*error = 1;
		nbr *= 10;
		nbr += str[i] - '0';
	}
	return (check_int(nbr, str, error, i));
}

t_args	*parser(int argc, char **argv)
{
	t_args	*args;
	int		error;

	error = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		exit(1);
	args->nbr_philo = ft_atou(argv[1], &error);
	args->time_die = ft_atou(argv[2], &error);
	args->time_eat = ft_atou(argv[3], &error);
	args->time_sleep = ft_atou(argv[4], &error);
	if (argc == 6)
		args->max_eats = ft_atou(argv[5], &error);
	else
		args->max_eats = INT_MAX;
	if (error == 1)
		main_errors(2, args);
	return (args);
}

void	check_min_values(t_args *args)
{
	if (args->nbr_philo == 0 || args->nbr_philo > 200)
		;
	else if (args->time_die < 60)
		;
	else if (args->time_eat < 60)
		;
	else if (args->time_sleep < 60)
		;
	else
		return ;
	main_errors(2, args);
}
