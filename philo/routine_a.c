/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 12:19:15 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil **phil)
{
	// pthread_mutex_lock(&(*phil)->left_fork->mutex);
	// msg_write(phil, "has taken a fork");
	// pthread_mutex_lock(&(*phil)->right_fork->mutex);
	// msg_write(phil, "has taken a fork");

    t_fork *first_fork;
    t_fork *second_fork;

    // Determine the locking order
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

    // Lock the forks in a consistent order
    pthread_mutex_lock(&first_fork->mutex);
    msg_write(phil, "has taken a fork");
    pthread_mutex_lock(&second_fork->mutex);
    msg_write(phil, "has taken a fork");

    msg_write(phil, "is eating");
    eat_smart_sleep(phil, (*phil)->env->eat_time);

	pthread_mutex_unlock(&first_fork->mutex);
    pthread_mutex_unlock(&second_fork->mutex);


	// msg_write(phil, "is eating");
	// eat_smart_sleep(phil, (*phil)->env->eat_time);
	// 	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	// 	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	(*phil)->meals++;
	if (full_check(phil))
	{
		pthread_mutex_lock(&(*phil)->env->state_mutex);
		(*phil)->env->full += 1;
		pthread_mutex_unlock(&(*phil)->env->state_mutex);	
	}
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
	int			i;

	i = 0;
	phil = (t_phil *)arg;

	if (one_phil_check(&phil))
		return (NULL);
	// if (phil->phil % 2 == 0)
	// 	usleep(500);
	while (general_full_check(&phil, i))
	{
		// if (phil->phil % 2 == 0)
		// 	smart_sleep(&phil, 1);
		if (!action(eat, &phil))
			break;
		// pthread_mutex_lock(&phil->env->write_mutex);
		// pthread_mutex_lock(&phil->env->full_mutex);
		// printf("Phil %u, meals %ld, must_meals %ld, env->full %u\n", phil->phil, phil->meals, phil->env->must_meals, phil->env->full);
		// pthread_mutex_unlock(&phil->env->full_mutex);
		// pthread_mutex_unlock(&phil->env->write_mutex);
		// if (full_check(&phil))	// Possible need to remove this break condition
		// 	break;
		if (!action(rest, &phil))
			break;
		if (!action(think, &phil))
			break;
	}

	return (NULL);
}