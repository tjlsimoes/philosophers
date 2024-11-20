/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/18 19:32:55 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil **phil)
{
	unsigned int	phil_nbr;

	phil_nbr = (*phil)->phil;
	pickup_forks(phil, phil_nbr);
	(*phil)->state = EATING;
	printf("%ld %u is eating\n", get_time(), phil_nbr);
	(*phil)->last_meal = get_time();
	smart_sleep(phil, (*phil)->eat_time);
	(*phil)->meals++;
	if (end_check(phil))
		return ;
	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	printf("%ld %u has released the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	printf("%ld %u has released the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
}

void	rest(t_phil **phil)
{
	(*phil)->state = SLEEPING;
	printf("%ld %u is sleeping\n", get_time(), (*phil)->phil);
	smart_sleep(phil, (*phil)->sleep_time);
}

void	think(t_phil **phil)
{
	(*phil)->state = THINKING;
	printf("%ld %u is thinking\n", get_time(), (*phil)->phil);
	smart_sleep(phil, THINK_TIME);
}

int	action(void (*f)(t_phil **), t_phil **phil)
{
	// unsigned int	action_time;

	// if (ACTION == EAT)
	// 	action_time = (*phil)->eat_time;
	// else if (ACTION == SLEEP)
	// 	action_time = (*phil)->sleep_time;
	// else
	// 	action_time = THINK_TIME;
	if (end_check(phil))
		return (0);
	// if (dead_check(get_time(), (*phil)->last_meal, (*phil)->die_time))
	// {
	// 	// (*phil)->state = DEAD;
	// 	// printf("%ld %u has died\n", get_time(), (*phil)->phil);
	// 	return (0);
	// }
	// if (dead_check(get_time() + action_time, (*phil)->last_meal, (*phil)->die_time))
	// {
	// 	smart_sleep(phil, action_time);
	// 	(*phil)->state = DEAD;
	// 	printf("%ld %u has died\n", get_time(), (*phil)->phil);
	// 	return (0);
	// }
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

	while (phil->meals < phil->must_meals)
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