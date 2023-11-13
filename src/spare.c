/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spare.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:19:53 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/04 12:58:47 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_dead(t_philo *root)
{
	pthread_mutex_lock(&root->deaths);
	if (root->died)
	{
		pthread_mutex_unlock(&root->deaths);
		return (true);
	}
	pthread_mutex_unlock(&root->deaths);
	return (false);
}

/* this func ensures that the simulation responds to the philosophers
** activities appropriately, monitoring for potential deaths and
** tracking meals completion*/
static void	ft_broadcast_death(t_philo *root)
{
	int	i;

	i = -1;
	while (++i < root->data->num_of_philo)
	{
		pthread_mutex_lock(&root->data->philosophers[i].deaths);
		root->data->philosophers[i].died = 1;
		pthread_mutex_unlock(&root->data->philosophers[i].deaths);
	}
}

int	ft_god_complement(t_philo *root)
{
	//long long	dead_at;
	bool		is_death;

	pthread_mutex_lock(&root->mtx_meal);
	is_death = root->data->currtime - root->last_meal
		- TIME_LOST >= root->data->t_die;
	if (is_death || root->data->n_must_eat == 0)
	{
		pthread_mutex_unlock(&root->mtx_meal);
		root->data->dead_philo = root->id;
		root->data->dead_at = root->data->currtime
			- root->data->t_init - TIME_LOST;
		if (is_death)
			root->data->death_cause = true;
		ft_broadcast_death(root);
		return (1);
	}
	pthread_mutex_unlock(&root->mtx_meal);
	return (0);
}
