// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init_c.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/11 16:15:50 by tjorge-l          #+#    #+#             */
// /*   Updated: 2024/11/11 16:23:47 by tjorge-l         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philosophers.h"

void	fork_lstclear(t_env **env, unsigned int lst_size)
{
	t_fork	*previous_node;
	t_fork	*current_node;
	unsigned int		i;

	if (!(*env)->fork)
		return ;
	i = 0;
	current_node = (*env)->fork;
	while (i < lst_size)
	{
		previous_node = current_node;
		current_node = previous_node->next;
		free(previous_node);
		previous_node = NULL;
		i++;
	}
	(*env)->fork = NULL;
}

void	fork_lstadd_back(t_env **env, t_fork *new, unsigned int i)
{
	t_fork	*node;

	if (!new)
		fork_lst_error("Error initializing fork struct.", env, i);
	new->fork = i;
	node = (*env)->fork;
	if (!node)
	{
		(*env)->fork = new;
		return ;
	}
	while (node->next != NULL)
		node = node->next;
	node->next = new;
}

void	fork_lst_check(t_env **env, unsigned int lst_size)
{
	t_fork			*node;
	unsigned int	i;

	node = (*env)->fork;
	i = 0;
	if (!node)
		return ;
	while (i < lst_size - 1)
	{
		printf("Current fork: %d\n", node->fork);
		printf("Next fork: %d\n", node->next->fork);
		node = node->next;
		i++;
	}
}
