/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:55:53 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/20 11:50:12 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	end_check(t_phil **phil)
{
	t_phil			*node;
	unsigned int	i;
	unsigned int	nbr_phil;
	int				all_full;

	i = 0;
	all_full = 1;
	node = *phil;
	nbr_phil = (*phil)->env->nbr_phil;
	while (i < nbr_phil)
	{
		if (node->state == DEAD)
			return (1);
		if (node->meals != node->env->must_meals)
			all_full = 0;
		node = node->right_phil;
		i++;
	}
	if (dead_check(get_time(),
		(*phil)->last_meal, (*phil)->env->die_time))
	{
		(*phil)->state = DEAD;
		printf("%ld %u has died\n", get_time(), (*phil)->phil);
		return (1);
	}
	if (all_full == 1)
		return (1);
	return (0);
}

long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec * 0.001);
}

int	dead_check(unsigned int current, unsigned int last, unsigned int die_time)
{
	if ((current - last) > die_time)
		return (1);
	return (0);
}

void pickup_forks(t_phil **phil, unsigned int phil_nbr)
{
	(*phil)->state = HUNGRY;
	if (phil_nbr == 1)
	{
		if (end_check(phil))
			return ;
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		printf("%ld %u has taken the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
		if (end_check(phil))
			return ;
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		printf("%ld %u has taken the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
	}
	else
	{
		if (end_check(phil))
			return ;
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		printf("%ld %u has taken the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
		if (end_check(phil))
			return ;
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		printf("%ld %u has taken the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
	}
}
