/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:14 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/04 13:47:01 by tjorge-l         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_posnbr(char *nptr)
{
	int		nbr;

	if (!nptr)
		return (0);
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		return (0);
	else if (*nptr == '+')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
		nbr = 1;
	return (nbr);
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
		printf("Time to die: %ld\n", node->env->die_time);
		printf("Time to eat: %ld\n", node->env->eat_time);
		printf("Time to sleep: %ld\n", node->env->sleep_time);
		printf("Necessary meals: %ld\n", node->env->must_meals);
		node = node->right_phil;
		i++;
	}
}
