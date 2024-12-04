/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:55:53 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 14:09:56 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	end_check(t_phil **phil)
{
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	if ((*phil)->env->dead != 0 || (*phil)->env->full == (*phil)->env->nbr_phil)
	{
		pthread_mutex_unlock(&(*phil)->env->state_mutex);
		return (1);
	}
	if (dead_check(get_time(), (*phil)->last_meal, (*phil)->env->die_time))
	{
		(*phil)->env->dead = 1;
		pthread_mutex_lock(&(*phil)->env->write_mutex);
		printf("%ld %u died\n", \
			get_time() - (*phil)->env->ini_time, (*phil)->phil);
		pthread_mutex_unlock(&(*phil)->env->write_mutex);
		pthread_mutex_unlock(&(*phil)->env->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

int	dead_check(long current, long last, long die_time)
{
	if ((current - last) > die_time)
		return (1);
	return (0);
}
