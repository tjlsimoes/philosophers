/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:50:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 14:32:19 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_phil_check(t_phil **phil)
{
	if ((*phil)->env->nbr_phil != 1)
		return (0);
	msg_write(phil, "has taken a fork");
	usleep((*phil)->env->die_time * 1000);
	printf("%ld %u died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	(*phil)->env->dead = 1;
	pthread_mutex_lock(&(*phil)->env->write_mutex);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
	return (1);
}

void	update_env_full(t_phil **phil)
{
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	(*phil)->env->full += 1;
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
}

void	update_dead(t_phil **phil)
{
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	if ((*phil)->env->dead != 1)
		(*phil)->env->dead = 1;
	else
	{
		pthread_mutex_unlock(&(*phil)->env->state_mutex);
		return ;
	}
	pthread_mutex_lock(&(*phil)->env->write_mutex);
	printf("%ld %u died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
}
