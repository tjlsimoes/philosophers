/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:00:09 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/13 13:23:23 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING
}	t_state;

typedef struct s_fork
{
	unsigned int	fork;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;

typedef struct s_phil
{
	unsigned int	phil;
	pthread_t		thread_id;
	t_state			state;
	unsigned int	meals;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	long			must_meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_phil	*left_phil;
	struct s_phil	*right_phil;
	
}	t_phil;

typedef struct s_env
{
	t_fork			*fork;
	t_phil			*philosopher;
	unsigned int	nbr_phil;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	long			must_meals;
}	t_env;

// Initial Error Check

void			check_args(int argc, char **argv);
void			error(char *error_msg);
void			phil_lst_error(char *error_msg,
					t_env **env, unsigned int idx);
void			fork_lst_error(char *error_msg, 
					t_env **env, unsigned int idx);
int				ft_isspace(char c);
int				ft_strlen(char *str);
int				is_posnbr(char *nptr);

// Initialer auxiliary functions

unsigned int	atui(char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);

void			philosophers_init(t_env **env);
void			phil_lstadd_back(t_env **env, t_phil *new, unsigned int i);
void			phil_lstclear(t_env **env, unsigned int lst_size);
void			phil_last_link(t_env **env);
void			phil_lst_check(t_env **env, unsigned int lst_size);

void			forks_init(t_env **env);
void			fork_lstclear(t_env **env, unsigned int lst_size);
void			fork_lstadd_back(t_env **env, t_fork *new, unsigned int i);
void			fork_lst_check(t_env **env, unsigned int lst_size);
t_fork			*get_fork_nbr(t_env **env, unsigned int nbr);

void			create_threads(t_env **env, unsigned int lst_size);
void			join_threads(t_env **env, unsigned int lst_size);
void			*mock(void *arg);


#endif