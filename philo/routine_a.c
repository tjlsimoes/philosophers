/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 14:05:42 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil **phil)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if ((*phil)->left_fork < (*phil)->right_fork)
	{
		first_fork = (*phil)->left_fork;
		second_fork = (*phil)->right_fork;
	}
	else
	{
		first_fork = (*phil)->right_fork;
		second_fork = (*phil)->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	msg_write(phil, "has taken a fork");
	pthread_mutex_lock(&second_fork->mutex);
	msg_write(phil, "has taken a fork");
	msg_write(phil, "is eating");
	eat_smart_sleep(phil, (*phil)->env->eat_time);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
	(*phil)->meals++;
	if (full_check(phil))
		update_env_full(phil);
}

void	rest(t_phil **phil)
{
	msg_write(phil, "is sleeping");
	smart_sleep(phil, (*phil)->env->sleep_time);
}

void	think(t_phil **phil)
{
	msg_write(phil, "is thinking");
	if (THINK_TIME)
		smart_sleep(phil, THINK_TIME);
}

int	action(void (*f)(t_phil **), t_phil **phil)
{
	if (end_check(phil))
		return (0);
	f(phil);
	return (1);
}

void	*routine(void *arg)
{
	t_phil		*phil;
	int			i;

	i = 0;
	phil = (t_phil *)arg;
	if (one_phil_check(&phil))
		return (NULL);
	if (phil->phil % 2 == 0)
		usleep(500);
	while (general_full_check(&phil, i))
	{
		if (!action(eat, &phil))
			break ;
		if (!action(rest, &phil))
			break ;
		if (!action(think, &phil))
			break ;
	}
	return (NULL);
}
