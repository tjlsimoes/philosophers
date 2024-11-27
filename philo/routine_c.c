/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:59:08 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/27 15:52:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_phil **phil,long time)
{

	if (end_check(phil))
		return ;
	time = get_time() + time;
	while (1)
	{
		if (get_time() > time)
			break;
		if (end_check(phil))
			break ;
		usleep(500);
		// printf("Here 1\n");
	}
}

int	eat_smart_sleep(t_phil **phil, long time)
{

	// if (end_check(phil))
	// {
	// 	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	// 	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	// 	return (0);
	// }
	time = get_time() + time;
	while (1)
	{
		// printf("Greater than: %ld %ld\n", get_time(), time);
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->right_fork->mutex);
			pthread_mutex_unlock(&(*phil)->left_fork->mutex);
			return (0);
		}
		if (get_time() > time)
			return (1);
		usleep(500);
		// printf("Here 2\n");
	}
}


void	msg_write(t_phil **phil, char *str)
{
	if (!str)
		return ;
	pthread_mutex_lock(&(*phil)->env->dead_mutex);
    if ((*phil)->env->dead)
	{
        pthread_mutex_unlock(&(*phil)->env->dead_mutex);
        return ;
    }

	pthread_mutex_lock(&(*phil)->env->write_mutex);
	printf("%ld %u %s\n", get_time() - (*phil)->env->ini_time, (*phil)->phil, str);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
    pthread_mutex_unlock(&(*phil)->env->dead_mutex);
}

int	full_check(t_phil **phil)
{
	if ((*phil)->env->must_meals != - 1
		&& (*phil)->meals == (*phil)->env->must_meals)
			return (1);
	return (0);
}

void	release_forks(t_phil **phil)
{
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		pthread_mutex_unlock(&(*phil)->right_fork->mutex);
		return ;
	}
	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	// msg_write(phil, "has released a fork");
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		return ;
	}
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	// msg_write(phil, "has released a fork");
}
