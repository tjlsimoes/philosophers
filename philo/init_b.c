/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:15:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/13 15:16:49 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_lstclear(t_env **env, unsigned int lst_size)
{
	t_phil				*previous_node;
	t_phil				*current_node;
	unsigned int		i;

	if (!(*env)->philosopher)
		return ;
	i = 0;
	current_node = (*env)->philosopher;
	while (i < lst_size)
	{
		previous_node = current_node;
		current_node = previous_node->right_phil;
		free(previous_node);
		previous_node = NULL;
		i++;
	}
	(*env)->philosopher = NULL;
}

void	phil_lstadd_back(t_env **env, t_phil *new, unsigned int i)
{
	t_phil	*node;

	if (!new)
		phil_lst_error("Error initializing philosopher struct.", env, i);
	new->phil = i;
	new->die_time = (*env)->die_time;
	new->eat_time = (*env)->eat_time;
	new->sleep_time = (*env)->sleep_time;
	new->must_meals = (*env)->must_meals;
	new->left_fork = get_fork_nbr(env, i - 1);
	new->right_fork = get_fork_nbr(env, i);
	node = (*env)->philosopher;
	if (!node)
	{
		(*env)->philosopher = new;
		return ;
	}
	while (node->right_phil != NULL)
		node = node->right_phil;
	node->right_phil = new;
	new->left_phil = node;
}

void	phil_last_link(t_env **env)
{
	t_phil	*node;

	node = (*env)->philosopher;
	if (!node)
		return ;
	while (node->right_phil != NULL)
		node = node->right_phil;
	node->right_phil = (*env)->philosopher;
	(*env)->philosopher->left_phil = node;
}

void	create_threads(t_env **env, unsigned int lst_size)
{
	t_phil			*node;
	unsigned int	i;

	node = (*env)->philosopher;
	i = 1;
	if (!node)
		return ;
	while (i <= lst_size)
	{
		pthread_create(&node->thread_id, NULL, routine, node);
		node = node->right_phil;
		i++;
	}
}

void	join_threads(t_env **env, unsigned int lst_size)
{
	t_phil			*node;
	unsigned int	i;

	node = (*env)->philosopher;
	i = 1;
	if (!node)
		return ;
	while (i <= lst_size)
	{
		pthread_join(node->thread_id, NULL);
		node = node->right_phil;
		i++;
	}
}

