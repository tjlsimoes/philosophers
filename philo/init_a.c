/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:12:14 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 16:16:35 by tjorge-l         ###   ########.fr       */
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
