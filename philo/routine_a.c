/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/20 18:35:28 by tjorge-l         ###   ########.fr       */
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
	if (!eat_smart_sleep(phil, (*phil)->env->eat_time))
		return ;
	(*phil)->meals++;
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		pthread_mutex_unlock(&(*phil)->right_fork->mutex);
		return ;
	}
	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	msg_write(phil, "has released a right fork");
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		return ;
	}
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	msg_write(phil, "has released a left fork");
}

void	rest(t_phil **phil)
{
	msg_write(phil, "is sleeping");
	smart_sleep(phil, (*phil)->env->sleep_time);
}

void	think(t_phil **phil)
{
	msg_write(phil, "is thinking");
	// smart_sleep(phil, THINK_TIME);
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
	// pthread_t 	tid;
	t_phil		*phil;

	phil = (t_phil *)arg;
	// tid = phil->thread_id;
	// printf("%ld Thread [%ld]\n", get_time(), tid);

	while (phil->meals < phil->env->must_meals)
	{
		if (!action(eat, &phil))
			break;
		if (!action(rest, &phil))
			break;
		if (!action(think, &phil))
			break;
	}

	return (NULL);
}