/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:55:53 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/25 15:17:48 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	end_check(t_phil **phil)
{
	pthread_mutex_lock(&(*phil)->env->dead_mutex);
	pthread_mutex_lock(&(*phil)->env->full_mutex);
	if ((*phil)->env->dead != 0 || (*phil)->env->full == (*phil)->env->nbr_phil)
	{
		pthread_mutex_unlock(&(*phil)->env->dead_mutex);
		pthread_mutex_unlock(&(*phil)->env->full_mutex);
		return (1);
	}
	if (dead_check(get_time(),
		(*phil)->last_meal, (*phil)->env->die_time))
	{
		(*phil)->env->dead = 1;
		pthread_mutex_lock(&(*phil)->env->write_mutex);
		printf("%lld %u has died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
		pthread_mutex_unlock(&(*phil)->env->write_mutex);
		pthread_mutex_unlock(&(*phil)->env->dead_mutex);
		pthread_mutex_unlock(&(*phil)->env->full_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*phil)->env->full_mutex);
	pthread_mutex_unlock(&(*phil)->env->dead_mutex);
	return (0);
}

long long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

int	dead_check(long long current, long long last, unsigned int die_time)
{
	if ((current - last) > die_time)
		return (1);
	return (0);
}

int pickup_forks(t_phil **phil, unsigned int phil_nbr)
{
	if (phil_nbr == 1)
	{
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->right_fork->mutex);
			return (-5);
		}
		msg_write(phil, "has taken a right fork");
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->right_fork->mutex);
			pthread_mutex_unlock(&(*phil)->left_fork->mutex);
			return (-5);
		}
		msg_write(phil, "has taken a left fork");
	}
	else
	{
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->left_fork->mutex);
			return (-5);
		}
		msg_write(phil, "has taken a left fork");
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->left_fork->mutex);
			pthread_mutex_unlock(&(*phil)->right_fork->mutex);
			return (-5);
		}
		msg_write(phil, "has taken a right fork");
	}
	return (1);
}
