/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:59:08 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/25 12:12:22 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_phil **phil, unsigned int time)
{
	unsigned int	i;

	if (end_check(phil))
		return ;
	i = 0;
	while (i < time)
	{
		if (i > time - 50)
		{
			usleep(time - i);
			break;
		}
		if (end_check(phil))
			break ;
		usleep(50);
		i += 50;
	}
}

int	eat_smart_sleep(t_phil **phil, unsigned int time)
{
	unsigned int	i;

	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->right_fork->mutex);
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		return (0);
	}
	i = 0;
	while (i < time)
	{
		if (i > time - 50)
		{
			usleep(time - i);
			break;
		}
		if (end_check(phil))
		{
			pthread_mutex_unlock(&(*phil)->right_fork->mutex);
			pthread_mutex_unlock(&(*phil)->left_fork->mutex);
			return (0);
		}
			break ;
		usleep(50);
		i += 50;
	}
	return (1);
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
	printf("%lld %u %s\n", get_time(), (*phil)->phil, str);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);

    pthread_mutex_unlock(&(*phil)->env->dead_mutex);
}

int	full_check(t_phil **phil)
{
	if ((*phil)->meals == (*phil)->env->must_meals
		&& (*phil)->env->must_meals != - 1)
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
	msg_write(phil, "has released a right fork");
	if (end_check(phil))
	{
		pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		return ;
	}
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	msg_write(phil, "has released a left fork");
}
