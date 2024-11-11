/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 16:20:09 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 6 && argc != 5)
		error("Invalid number of arguments.\n");
	i = 1;
	while (i < argc)
	{
		if (!is_posnbr(argv[i]))
			error("Invalid argument.\n");
		i++;
	}
}

t_phil	*philosophers_init(char **argv)
{
	t_phil			*philosopher;
	unsigned int 	i;

	i = 0;
	philosopher = NULL;
	while (i < atui(argv[1]))
	{
		printf("Node %i\n", i); //
		phil_lstadd_back(&philosopher,
			(t_phil *)ft_calloc(1, sizeof(t_phil)), i);
		if (i == atui(argv[1]) - 1)
			phil_last_link(&philosopher);
		i++;
	}
	phil_lst_check(&philosopher, atui(argv[1])); //
	return (philosopher);
}

int	main(int argc, char **argv)
{
	t_phil			*philosopher;

	check_args(argc, argv);
	philosopher = philosophers_init(argv);

	phil_lstclear(&philosopher, atui(argv[1]));
	return (0);
}
