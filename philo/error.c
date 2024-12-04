/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:51:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 13:46:55 by tjorge-l         ###   ########.fr       */
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

void	fork_lst_error(char *error_msg, t_env **env, unsigned int idx)
{
	fork_lstclear(env, idx);
	free(env);
	error(error_msg);
}

void	phil_lst_error(char *error_msg, t_env **env, unsigned int idx)
{
	fork_lstclear(env, idx);
	phil_lstclear(env, idx);
	free(env);
	error(error_msg);
}
