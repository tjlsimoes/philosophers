/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:00:09 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/11/11 16:12:33 by tjorge-l         ###   ########.fr       */
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
}	t_fork;

typedef struct s_phil
{
	unsigned int	phil;
	t_state			state;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned int	meals;
	struct s_phil	*left_phil;
	struct s_phil	*right_phil;
	
}	t_phil;

// Initial Error Check

void			check_args(int argc, char **argv);
void			error(char *error_msg);
void			lst_error(char *error_msg, 
					t_phil **philosopher,unsigned int idx);
int				ft_isspace(char c);
int				ft_strlen(char *str);
int				is_posnbr(char *nptr);
void			phil_lstclear(t_phil **lst, unsigned int lst_size);


// Initialer auxiliary functions

unsigned int	atui(char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);
void			phil_lstadd_back(t_phil **lst, t_phil *new, unsigned int i);
void			phil_last_link(t_phil **lst);
void			phil_lst_check(t_phil **lst, unsigned int lst_size);
#endif