/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:52:19 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/04 12:59:15 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

// Reflects the time in (milliseconds) between initialization of philosophers.
# ifndef SPAWN_RATE
#  define SPAWN_RATE 1
#  define TIME_LOST 50
# endif

typedef struct s_fork{
	pthread_mutex_t	*m_fork;
	int				id;
}	t_fork;

typedef struct s_god
{
	short	all_ate;
	int		num_of_meals;
}	t_god;

typedef struct s_philo
{
	int				id;
	int				num_of_meals;
	long long		last_meal;
	pthread_mutex_t	mtx_meal;
	t_fork			left_fork;
	t_fork			right_fork;
	pthread_mutex_t	mtx_nb_meal;
	short			died;
	short			stop;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	deaths;
}	t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				n_must_eat;
	long long		t_init;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	t_philo			*philosophers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	long long		currtime;
	t_god			god;
	long long		dead_at;
	int				dead_philo;
	bool			death_cause;
	short			all_ate;
}	t_data;

// ####### ACTIVITY.C #########
void			*ft_action(void *philosopher);
bool			is_dead(t_philo *root);

// ######  SPARE.C ###########
//static void		ft_grab_forks(t_philo *root);
int				ft_god_complement(t_philo *root);
int				ft_safety_check(t_data *data);
int				ft_initialize_philo_mtx(t_data *data, int i);

// ####### CHECK.C ########
int				ft_check_data(t_data *data, int argc);
void			*ft_god(void *in_data);
int				ft_check_argc(int argc);
int				ft_check_is_num(char **argv);
// ####### UTILITIES.C ########
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
long long		ft_get_time(void);
long long		ft_abs_time(t_philo *root);
void			ft_print(t_philo *root, char *str);
// ####### UTILITIES2.C #######
void			ft_destroy_mutex_fork(t_data *data);
void			ft_destroy_free(t_data *data);
// ####### INITIALIZE.C ######
int				ft_initialize_data(t_data *data, int argc, char **argv);
int				ft_initialize_print(t_data *data);
int				ft_initialize_fork(t_data *data);
int				ft_initialize_philo(t_data *data);
int				ft_initialize_simulation(t_data *data);

#endif
