/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:59:08 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/18 19:12:51 by tjorge-l         ###   ########.fr       */
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
