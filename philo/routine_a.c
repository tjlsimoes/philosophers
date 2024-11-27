/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/25 17:00:34 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil **phil)
{
	unsigned int	phil_nbr;

	phil_nbr = (*phil)->phil;
	if (pickup_forks(phil, phil_nbr) == -5)
		return ;
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		pthread_mutex_unlock(&(*phil)->right_fork->mutex);
		return ;
	}
	msg_write(phil, "is eating");
	(*phil)->last_meal = get_time();
	if (!eat_smart_sleep(phil, (*phil)->env->eat_time * 1000))
		return ;
	(*phil)->meals++;
	if (full_check(phil))
	{
		pthread_mutex_lock(&(*phil)->env->full_mutex);
		(*phil)->env->full += 1;
		pthread_mutex_unlock(&(*phil)->env->full_mutex);	
	}
	release_forks(phil);
}

void	rest(t_phil **phil)
{
	msg_write(phil, "is sleeping");
	smart_sleep(phil, (*phil)->env->sleep_time * 1000);
}

void	think(t_phil **phil)
{
	msg_write(phil, "is thinking");
	// smart_sleep(phil, THINK_TIME * 1000);
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

	phil = (t_phil *)arg;

	if (one_phil_check(&phil))
		return (NULL);
	while (1)
	{
		if (!action(eat, &phil))
			break;
		// pthread_mutex_lock(&phil->env->write_mutex);
		// pthread_mutex_lock(&phil->env->full_mutex);
		// printf("Phil %u, meals %ld, must_meals %ld, env->full %u\n", phil->phil, phil->meals, phil->env->must_meals, phil->env->full);
		// pthread_mutex_unlock(&phil->env->full_mutex);
		// pthread_mutex_unlock(&phil->env->write_mutex);
		if (full_check(&phil))
			break;
		if (!action(rest, &phil))
			break;
		if (!action(think, &phil))
			break;
	}

	return (NULL);
}