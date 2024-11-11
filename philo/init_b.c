/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 16:16:45 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_lstclear(t_phil **lst, unsigned int lst_size)
{
	t_phil	*previous_node;
	t_phil	*current_node;
	unsigned int		i;

	if (!lst)
		return ;
	i = 0;
	current_node = *lst;
	while (i < lst_size)
	{
		previous_node = current_node;
		current_node = previous_node->right_phil;
		free(previous_node);
		previous_node = NULL;
		i++;
	}
	*lst = NULL;
}

void	phil_lstadd_back(t_phil **lst, t_phil *new, unsigned int i)
{
	t_phil	*node;

	if (!new)
		lst_error("Error initializing philosopher struct.", lst, i);
	new->phil = i;
	node = *lst;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (node->right_phil != NULL)
		node = node->right_phil;
	node->right_phil = new;
	new->left_phil = node;
}

void	phil_last_link(t_phil **lst)
{
	t_phil	*node;

	node = *lst;
	if (!node)
		return ;
	while (node->right_phil != NULL)
		node = node->right_phil;
	node->right_phil = *lst;
	(*lst)->left_phil = node;
}

void	phil_lst_check(t_phil **lst, unsigned int lst_size)
{
	t_phil			*node;
	unsigned int	i;

	node = *lst;
	i = 0;
	if (!node)
		return ;
	while (i < lst_size)
	{
		printf("Current philosopher: %d\n", node->phil);
		printf("Philosopher to the left: %d\n", node->left_phil->phil);
		printf("Philosopher to the right: %d\n", node->right_phil->phil);
		node = node->right_phil;
		i++;
	}
}
