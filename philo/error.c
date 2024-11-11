/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:51:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 16:40:42 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	exit(1);
}

// void	fork_lst_error(char *error_msg, t_fork **fork, unsigned int idx)
// {
// 	fork_lstclear(fork, idx);
// 	write(2, error_msg, ft_strlen(error_msg));
// 	exit(1);
// }

void	phil_lst_error(char *error_msg, t_env **env, unsigned int idx)
{
	// fork_lstclear((*env)->fork, idx);
	phil_lstclear(env, idx);
	free(env);
	error(error_msg);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_posnbr(char *nptr)
{
	int		nbr;

	if (!nptr)
		return (0);
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		return (0);
	else if (*nptr == '+')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
		nbr = 1;
	return (nbr);
}
