/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:59:08 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 12:09:15 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_phil **phil,long time)
{
	long	beginning;
	long	check;

	if (end_check(phil))
		return ;
	beginning = get_time();
	check = beginning + 9;
	while ((get_time() - beginning) < time)
	{
		// if (get_time() > time)
		// 	break;
		// if (end_check(phil))
		// 	break ;
		if (get_time() == check)
		{
			if (dead_check(get_time(), (*phil)->last_meal, (*phil)->env->die_time))
			{
				pthread_mutex_lock(&(*phil)->env->state_mutex);
				if ((*phil)->env->dead != 1)
					(*phil)->env->dead = 1;
				else
				{
					pthread_mutex_unlock(&(*phil)->env->state_mutex);
				}
				pthread_mutex_lock(&(*phil)->env->write_mutex);
				printf("%ld %u died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
				pthread_mutex_unlock(&(*phil)->env->write_mutex);
				pthread_mutex_unlock(&(*phil)->env->state_mutex);
			}
			check += 10;
		}
		usleep(250);
		// printf("Here 1\n");
	}
}

int	eat_smart_sleep(t_phil **phil, long time)
{
	long	beginning;
	long	check;
	// if (end_check(phil))
	// {
	// 	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	// 	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	// 	return (0);
	// }
	beginning = get_time();
	check = beginning + 9;
	while ((get_time() - beginning) < time)
	{
		// printf("Greater than: %ld %ld\n", get_time(), time);
		// if (end_check(phil))
		// {
		// 	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
		// 	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
		// 	return (0);
		// }
		// if (get_time() > time)
		// 	return (1);
		if (get_time() == check)
		{
			if (dead_check(get_time(), (*phil)->last_meal, (*phil)->env->die_time))
			{
				pthread_mutex_lock(&(*phil)->env->state_mutex);
				if ((*phil)->env->dead != 1)
					(*phil)->env->dead = 1;
				else
				{
					pthread_mutex_unlock(&(*phil)->env->state_mutex);
					return (1);
				}
				pthread_mutex_lock(&(*phil)->env->write_mutex);
				printf("%ld %u died\n", get_time() - (*phil)->env->ini_time, (*phil)->phil);
				pthread_mutex_unlock(&(*phil)->env->write_mutex);
				pthread_mutex_unlock(&(*phil)->env->state_mutex);
				return (1);
			}
			check += 10;
		}

		usleep(250);
		// printf("Here 2\n");
	}
	(*phil)->last_meal = get_time();
	return (1);
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
	printf("%ld %u %s\n", get_time() - (*phil)->env->ini_time, (*phil)->phil, str);
	pthread_mutex_unlock(&(*phil)->env->write_mutex);
    pthread_mutex_unlock(&(*phil)->env->state_mutex);
}

int	full_check(t_phil **phil)
{
	if ((*phil)->env->must_meals != - 1
		&& (*phil)->meals == (*phil)->env->must_meals)
			return (1);
	return (0);
}

int general_full_check(t_phil **phil, int i)
{
	if (i % 5 != 0)
		return (1);
	pthread_mutex_lock(&(*phil)->env->state_mutex);
	if ((*phil)->env->nbr_phil == (*phil)->env->full)
		return (pthread_mutex_unlock(&(*phil)->env->state_mutex), 0);
	pthread_mutex_unlock(&(*phil)->env->state_mutex);
	return (1);
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
