/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/27 15:40:44 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil **phil)
{
	unsigned int	phil_nbr;

	phil_nbr = (*phil)->phil;
	// if (pickup_forks(phil, phil_nbr) == -5)
	// 	return ;
	pickup_forks(phil, phil_nbr);
	// if (end_check(phil))
	// {
	// 	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	// 	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	// 	return ;
	// }
	msg_write(phil, "is eating");
	if (!eat_smart_sleep(phil, (*phil)->env->eat_time))
		return ;
	(*phil)->last_meal = get_time();
	(*phil)->meals++;
	if (full_check(phil))
	{
		pthread_mutex_lock(&(*phil)->env->full_mutex);
		(*phil)->env->full += 1;
		pthread_mutex_unlock(&(*phil)->env->full_mutex);	
	}
	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
}

void	rest(t_phil **phil)
{
	msg_write(phil, "is sleeping");
	smart_sleep(phil, (*phil)->env->sleep_time);
}

void	think(t_phil **phil)
{
	msg_write(phil, "is thinking");
	// smart_sleep(phil, THINK_TIME );
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
	// if (phil->phil % 2 == 0)
	// 	usleep(500);
	while (1)
	{
		if (!action(eat, &phil))
			break;
		// pthread_mutex_lock(&phil->env->write_mutex);
		// pthread_mutex_lock(&phil->env->full_mutex);
		// printf("Phil %u, meals %ld, must_meals %ld, env->full %u\n", phil->phil, phil->meals, phil->env->must_meals, phil->env->full);
		// pthread_mutex_unlock(&phil->env->full_mutex);
		// pthread_mutex_unlock(&phil->env->write_mutex);
		if (full_check(&phil))	// Possible need to remove this break condition
			break;
		if (!action(rest, &phil))
			break;
		if (!action(think, &phil))
			break;
	}

	return (NULL);
}