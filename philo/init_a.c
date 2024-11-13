/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:14 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/13 15:58:22 by tjorge-l         ###   ########.fr       */
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

void	*mock(void *arg)
{
	pthread_t tid;

	if (!arg)
		printf("No arg!\n");

	// tid = pthread_self();
	tid = ((t_phil *)arg)->thread_id;
	printf("Thread [%ld]\n", tid);

	return (NULL);
}

long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec * 0.001);
}

void	eat(t_phil **phil)
{
	unsigned int	phil_nbr;

	phil_nbr = (*phil)->phil;
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
		(*phil)->state = EATING;
		printf("%ld %u is eating\n", get_time(), phil_nbr);
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

void	*routine(void *arg)
{
	pthread_t 	tid;
	t_phil		*phil;

	phil = (t_phil *)arg;
	tid = phil->thread_id;
	printf("%ld Thread [%ld]\n", get_time(), tid);

	while (phil->meals < phil->must_meals)
	{
		eat(&phil);
		rest(&phil);
		think(&phil);
	}

	return (NULL);
}
