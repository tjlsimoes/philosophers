/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:14 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/18 18:27:55 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*array;

	if (nmemb > INT_MAX || size > INT_MAX)
		return (NULL);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (array);
	memset(array, 0, nmemb * size);
	return (array);
}

unsigned int	atui(char *nptr)
{
	unsigned int		nbr;

	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
	}
	return (nbr);
}

void	phil_lst_check(t_env **env, unsigned int lst_size)
{
	t_phil			*node;
	unsigned int	i;

	node = (*env)->philosopher;
	i = 1;
	if (!node)
		return ;
	while (i <= lst_size)
	{
		printf("Current philosopher: %d\n", node->phil);
		printf("Fork to the left: %d\n", node->left_fork->fork);
		printf("Fork to the right: %d\n", node->right_fork->fork);
		printf("Philosopher to the left: %d\n", node->left_phil->phil);
		printf("Philosopher to the right: %d\n", node->right_phil->phil);
		printf("Time to die: %u\n", node->die_time);
		printf("Time to eat: %u\n", node->eat_time);
		printf("Time to sleep: %u\n", node->sleep_time);
		printf("Necessary meals: %ld\n", node->must_meals);
		node = node->right_phil;
		i++;
	}
}

int	end_check(t_phil **phil)
{
	t_phil			*node;
	unsigned int	i;
	unsigned int	nbr_phil;
	int				all_full;

	i = 0;
	all_full = 1;
	node = *phil;
	nbr_phil = (*phil)->nbr_phil;
	while (i < nbr_phil)
	{
		if (node->state == DEAD)
			return (1);
		if (node->meals != node->must_meals)
			all_full = 0;
		node = node->right_phil;
		i++;
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
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		printf("%ld %u has taken the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		printf("%ld %u has taken the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&(*phil)->left_fork->mutex);
		printf("%ld %u has taken the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
		pthread_mutex_lock(&(*phil)->right_fork->mutex);
		printf("%ld %u has taken the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
	}
}

void	eat(t_phil **phil)
{
	unsigned int	phil_nbr;

	phil_nbr = (*phil)->phil;
	pickup_forks(phil, phil_nbr);
	(*phil)->state = EATING;
	printf("%ld %u is eating\n", get_time(), phil_nbr);
	(*phil)->last_meal = get_time();
	usleep((*phil)->eat_time);
	(*phil)->meals++;
	pthread_mutex_unlock(&(*phil)->right_fork->mutex);
	printf("%ld %u has released the right fork %u\n", get_time(), phil_nbr, (*phil)->right_fork->fork);
	pthread_mutex_unlock(&(*phil)->left_fork->mutex);
	printf("%ld %u has released the left fork %u\n", get_time(), phil_nbr, (*phil)->left_fork->fork);
}

void	rest(t_phil **phil)
{
	(*phil)->state = SLEEPING;
	printf("%ld %u is sleeping\n", get_time(), (*phil)->phil);
	usleep((*phil)->sleep_time);
}

void	think(t_phil **phil)
{
	(*phil)->state = THINKING;
	printf("%ld %u is thinking\n", get_time(), (*phil)->phil);
	usleep(THINK_TIME);
}

int	action(t_action ACTION, void (*f)(t_phil **), t_phil **phil)
{
	unsigned int	action_time;

	if (ACTION == EAT)
		action_time = (*phil)->eat_time;
	else if (ACTION == SLEEP)
		action_time = (*phil)->sleep_time;
	else
		action_time = THINK_TIME;
	if (dead_check(get_time(), (*phil)->last_meal, (*phil)->die_time))
	{
		(*phil)->state = DEAD;
		printf("%ld %u has died\n", get_time(), (*phil)->phil);
		return (0);
	}
	if (dead_check(get_time() + action_time, (*phil)->last_meal, (*phil)->die_time))
	{
		printf("%u will die during %i\n", (*phil)->phil, (int)ACTION);
		usleep(action_time);
		(*phil)->state = DEAD;
		printf("%ld %u has died\n", get_time(), (*phil)->phil);
		return (0);
	}
	if (end_check(phil))
		return (0);
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
		if (!action(EAT, eat, &phil))
			break;
		if (!action(SLEEP, rest, &phil))
			break;
		if (!action(THINK, think, &phil))
			break;
	}

	return (NULL);
}
