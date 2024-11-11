/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 19:17:34 by tjorge-l         ###   ########.fr       */
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

void	philosophers_init(t_env **env, char **argv)
{
	unsigned int 	i;

	i = 1;
	while (i <= atui(argv[1]))
	{
		phil_lstadd_back(env,
			(t_phil *)ft_calloc(1, sizeof(t_phil)), i);
		if (i == atui(argv[1]))
			phil_last_link(env);
		i++;
	}
	phil_lst_check(env, atui(argv[1])); //
}

void	forks_init(t_env **env, char **argv)
{
	unsigned int 	i;

	i = 1;
	while (i <= atui(argv[1]))
	{
		fork_lstadd_back(env,
			(t_fork *)ft_calloc(1, sizeof(t_fork)), i);
		i++;
	}
	fork_lst_check(env, atui(argv[1])); //
}

int	main(int argc, char **argv)
{
	t_env			*env;

	check_args(argc, argv);
	env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!env)
		error("Failed to create env variable.\n");
	forks_init(&env, argv);
	philosophers_init(&env, argv);

	fork_lstclear(&env, atui(argv[1]));
	phil_lstclear(&env, atui(argv[1]));
	free(env);
	return (0);
}
