/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:47 by ankinzin          #+#    #+#             */
/*   Updated: 2023/08/18 15:30:52 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_sleep(t_philo *root)
{
	ft_print(root, "is sleeping");
	usleep(root->data->t_sleep * 1000);
}

/* This func is responsible for letting us know that a philosopher is eating
** recording the time they started, simulating the time they spend eating
** and then releasing forks once they're done eating and keeps track
** of how many meals philo's has eaten*/
static void	ft_eat(t_philo *root)
{
	ft_print(root, "is eating");
	root->last_meal = ft_get_time();
	usleep(root->data->t_eat * 1000);
	pthread_mutex_unlock(root->left_fork);
	pthread_mutex_unlock(root->right_fork);
	root->num_of_meals++;
}

/* This func helps a philosopher pickup necessary forks and eat by first
** picking the left fork and announces it, and then check if there's only
** one philosopher present if one we waits and returns, if there's more we
** pick right fork too*/
static int	ft_grab_forks(t_philo *root)
{
	pthread_mutex_lock(root->left_fork);
	ft_print(root, "has taken a fork");
	if (root->data->num_of_philo == 1)
	{
		usleep(root->data->t_eat * 1000);
		return (0);
	}
	if (root->data->god.died)
		return (0);
	pthread_mutex_lock(root->right_fork);
	ft_print(root, "has taken a fork");
	return (1);
}


bool	is_dead(t_philo *root)
{
	pthread_mutex_lock(&root->data->deaths);
	if (root->data->god.died)
	{
		pthread_mutex_unlock(&root->data->deaths);
		return (true);
	}
	pthread_mutex_unlock(&root->data->deaths);
	return (false);
}

/* This func represents the actions of a philo while they're on the
** table, the philo repeatedly goes through a loop that simulates their
** activities god(is like the manager) which handles all activities
** and stop them also if needed*/
void	*ft_action(void *philosopher)
{
	t_philo	*root;

	root = (t_philo *)philosopher;
	root->last_meal = ft_get_time();
	if (root->id % 2)
		usleep((root->data->t_eat * 1000) / 2);
	while (1)
	{
		if (is_dead(root))
			break ;
		// if (root->data->god.died)
		// 	break ;
		if (!ft_grab_forks(root))
			break ;
		if (is_dead(root))
			break ;
		// if (root->data->god.died)
		// 	break ;
		ft_eat(root);
		if (is_dead(root))
			break ;
		if ((root->num_of_meals == root->data->n_must_eat || root->data->god.all_ate))
			break ;
		ft_sleep(root);
		if (is_dead(root))
			break ;
		// if (root->data->god.died)
		// 	break ;
		ft_print(root, "is thinking");
	}
	return ((void *)root);
}
