/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:59:08 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 14:36:26 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_phil **phil, long time)
{
	long	beginning;
	long	check;

	if (end_check(phil))
		return ;
	beginning = get_time();
	check = beginning + 9;
	while ((get_time() - beginning) < time)
	{
		if (get_time() == check)
		{
			if (dead_check(get_time(), (*phil)->last_meal, \
				(*phil)->env->die_time))
				return (update_dead(phil));
			check += 10;
		}
		usleep(250);
	}
}

void	eat_smart_sleep(t_phil **phil, long time)
{
	long	beginning;
	long	check;

	beginning = get_time();
	check = beginning + 9;
	while ((get_time() - beginning) < time)
	{
		if (get_time() == check)
		{
			if (dead_check(get_time(), (*phil)->last_meal, \
				(*phil)->env->die_time))
				return (update_dead(phil));
			check += 10;
		}
		usleep(250);
	}
	(*phil)->last_meal = get_time();
}

void	msg_write(t_phil **phil, char *str)
{
	if (!str)
		return ;
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	if ((*phil)->env->dead)
	{
		pthread_mutex_unlock(&(*phil)->env->state_mutex);
		return ;
	}
	pthread_mutex_lock(&(*phil)->env->write_mutex);
	printf("%ld %u %s\n", \
		get_time() - (*phil)->env->ini_time, (*phil)->phil, str);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
}

int	full_check(t_phil **phil)
{
	if ((*phil)->env->must_meals != -1 \
		&& (*phil)->meals == (*phil)->env->must_meals)
		return (1);
	return (0);
}

int	general_full_check(t_phil **phil, int i)
{
	if (i % 5 != 0)
		return (1);
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	if ((*phil)->env->nbr_phil == (*phil)->env->full)
		return (pthread_mutex_unlock(&(*phil)->env->state_mutex), 0);
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
	return (1);
}
