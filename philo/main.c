/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/13 15:56:25 by tjorge-l         ###   ########.fr       */
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
		if (i == 1 && atui(argv[i]) <= 0)
			error("Invalid argument.\n");
		i++;
	}
}

void	philosophers_init(t_env **env)
{
	unsigned int 	i;

	i = 1;
	while (i <= (*env)->nbr_phil)
	{
		phil_lstadd_back(env,
			(t_phil *)ft_calloc(1, sizeof(t_phil)), i);
		if (i == (*env)->nbr_phil)
			phil_last_link(env);
		i++;
	}
	// phil_lst_check(env, (*env)->nbr_phil); //
}

void	forks_init(t_env **env)
{
	unsigned int 	i;

	i = 1;
	while (i <= (*env)->nbr_phil)
	{
		fork_lstadd_back(env,
			(t_fork *)ft_calloc(1, sizeof(t_fork)), i);
		i++;
	}
}

t_env	*env_init(int argc, char **argv)
{
	t_env	*env;

	env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!env)
		error("Failed to create env variable.\n");
	env->die_time = atui(argv[2]);
	env->eat_time = atui(argv[3]);
	env->sleep_time = atui(argv[4]);
	if (argc == 6)
		env->must_meals = atui(argv[5]);
	else
		env->must_meals = -1;
	env->nbr_phil = atui(argv[1]);
	return (env);
}

int	main(int argc, char **argv)
{
	t_env			*env;

	check_args(argc, argv);
	env = env_init(argc, argv);
	forks_init(&env);
	philosophers_init(&env);

	create_threads(&env, env->nbr_phil);
	join_threads(&env, env->nbr_phil);

	fork_lstclear(&env, env->nbr_phil);
	phil_lstclear(&env, env->nbr_phil);
	free(env);
	return (0);
}
