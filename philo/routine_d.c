/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:50:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/25 15:13:50 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_phil_check(t_phil **phil)
{
	if ((*phil)->env->nbr_phil != 1)
		return (0);
	msg_write(phil, "has taken a right fork");
	usleep((*phil)->env->die_time);
	pthread_mutex_lock(&(*phil)->env->dead_mutex);
	(*phil)->env->dead = 1;
	pthread_mutex_lock(&(*phil)->env->write_mutex);
	printf("%lld %u has died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
	pthread_mutex_unlock(&(*phil)->env->dead_mutex);
	return (1);
}
