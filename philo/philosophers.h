/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:00:09 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/12/10 10:09:53 by tjorge-l         ###   ########.fr       */
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
	struct s_env	*env;
	long			meals;
	long			last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_phil	*left_phil;
	struct s_phil	*right_phil;

}	t_phil;

typedef struct s_env
{
	long			ini_time;
	t_fork			*fork;
	t_phil			*philosopher;
	int				dead;
	unsigned int	full;
	unsigned int	nbr_phil;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			must_meals;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	state_mutex;
}	t_env;

// Main auxiliary functions
void			check_args(int argc, char **argv);
void			philosophers_init(t_env **env);
void			forks_init(t_env **env);
t_env			*env_init(int argc, char **argv);

// Initial Error Check
void			error(char *error_msg);
void			phil_lst_error(char *error_msg,
					t_env **env, unsigned int idx);
void			fork_lst_error(char *error_msg,
					t_env **env, unsigned int idx);
int				ft_strlen(char *str);

// Initializer auxiliary functions
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isspace(char c);
int				is_posnbr(char *nptr);
unsigned int	atui(char *nptr);
void			phil_lst_check(t_env **env, unsigned int lst_size);

void			phil_lstclear(t_env **env, unsigned int lst_size);
void			phil_lstadd_back(t_env **env, t_phil *new, unsigned int i);
void			phil_last_link(t_env **env);
int				create_threads(t_env **env, unsigned int lst_size);
void			join_threads(t_env **env, unsigned int lst_size);

void			fork_lstclear(t_env **env, unsigned int lst_size);
void			fork_lstadd_back(t_env **env, t_fork *new, unsigned int i);
void			fork_lst_check(t_env **env, unsigned int lst_size);
t_fork			*get_fork_nbr(t_env **env, unsigned int nbr);

// Routine functions
void			eat(t_phil **phil);
void			rest(t_phil **phil);
void			think(t_phil **phil);
int				action(void (*f)(t_phil **), t_phil **phil);
void			*routine(void *arg);

int				end_check(t_phil **phil);
long			get_time(void);
int				dead_check(long current, long last, long die_time);

void			smart_sleep(t_phil **phil, long time);
void			eat_smart_sleep(t_phil **phil, long time);
void			msg_write(t_phil **phil, char *str);
int				full_check(t_phil **phil);
int				general_full_check(t_phil **phil, int i);

int				one_phil_check(t_phil **phil);
void			update_env_full(t_phil **phil);
void			update_dead(t_phil **phil);

#endif