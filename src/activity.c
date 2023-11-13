/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:47 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/02 17:05:35 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* This func helps a philosopher pickup necessary forks and eat by first
** picking the left fork and announces it, and then check if there's only
** one philosopher present if one we waits and returns, if there's more we
** pick right fork too*/
static void	ft_grab_forks(t_philo *root)
{
	long long	time_ms;
	long long	time_2_ms;

	if (is_dead(root))
		return ;
	time_ms = (ft_get_time() - root->data->t_init);
	time_2_ms = (ft_get_time() - root->data->t_init);
	pthread_mutex_lock(&root->data->print);
	printf("%lld %d has taken a fork\n", time_ms, root->id);
	printf("%lld %d has taken a fork\n", time_2_ms, root->id);
	pthread_mutex_unlock(&root->data->print);
}

static void	ft_sleep(t_philo *root)
{
	long long	start_sleeping;
	long long	finish;

	start_sleeping = ft_get_time();
	finish = root->data->t_sleep + start_sleeping;
	if (is_dead(root))
		return ;
	ft_print(root, "is sleeping");
	while (ft_get_time() < finish)
	{
		if (is_dead(root))
			return ;
		usleep(500);
	}
}

/* This func is responsible for letting us know that a philosopher is eating
** recording the time they started, simulating the time they spend eating
** and then releasing forks once they're done eating and keeps track
** of how many meals philo's has eaten*/
static void	ft_eat(t_philo *root)
{
	long long	finish;
	long long	start_eating;

	start_eating = ft_get_time();
	pthread_mutex_lock(&root->mtx_meal);
	root->last_meal = ft_get_time();
	if (root->num_of_meals > 0)
		root->num_of_meals -= 1;
	pthread_mutex_unlock(&root->mtx_meal);
	finish = root->data->t_eat + start_eating;
	if (is_dead(root))
		return ;
	pthread_mutex_lock(&root->data->print);
	printf("%lld %d eating\n", start_eating - root->data->t_init, root->id);
	pthread_mutex_unlock(&root->data->print);
	while (ft_get_time() < finish)
	{
		if (is_dead(root))
			return ;
		usleep(500);
	}
	return ;
}

static void	ft_think(t_philo *root)
{
	long long	t_think;
	long long	curr_time;
	long long	stop_thinking_at;

	curr_time = ft_get_time();
	if (is_dead(root))
		return ;
	pthread_mutex_lock(&root->mtx_meal);
	t_think = (root->data->t_die - (ft_get_time()
				- root->last_meal) - root->data->t_eat) / 2;
	if (t_think < 0)
		t_think = 0;
	if (t_think > 600)
		t_think = 200;
	stop_thinking_at = t_think + curr_time;
	pthread_mutex_unlock(&root->mtx_meal);
	pthread_mutex_lock(&root->data->print);
	printf("%lld %d is thinking\n", curr_time - root->data->t_init, root->id);
	pthread_mutex_unlock(&root->data->print);
	while (ft_get_time() < stop_thinking_at)
	{
		if (is_dead(root))
			return ;
		usleep(500);
	}
}

/* This func represents the actions of a philo while they're on the
** table, the philo repeatedly goes through a loop that simulates their
** activities god(is like the manager) which handles all activities
** and stop them also if needed*/
void	*ft_action(void *philosopher)
{
	t_philo	*root;

	root = (t_philo *)philosopher;
	while (1)
	{
		if (root->id % 2)
			usleep(1000);
		if (is_dead(root))
			break ;
		pthread_mutex_lock(root->left_fork.m_fork);
		pthread_mutex_lock(root->right_fork.m_fork);
		ft_grab_forks(root);
		ft_eat(root);
		pthread_mutex_unlock(root->right_fork.m_fork);
		pthread_mutex_unlock(root->left_fork.m_fork);
		ft_sleep(root);
		ft_think(root);
	}
	return (NULL);
}
