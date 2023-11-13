/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spare2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:50:27 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/02 17:51:03 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_initialize_philo_mtx(t_data *data, int i)
{
	if (pthread_mutex_init(&data->philosophers[i].mtx_meal, NULL))
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free(data->fork);
		printf("Error: mutex last meal failed\n");
		return (0);
	}
	if (pthread_mutex_init(&data->philosophers[i].mtx_nb_meal, NULL))
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free(data->fork);
		printf("Error: mutex last meal failed\n");
		return (0);
	}
	if (pthread_mutex_init(&data->philosophers[i].deaths, NULL))
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free(data->fork);
		printf("Error: mutex last meal failed\n");
		return (0);
	}
	return (1);
}

int	ft_safety_check(t_data *data)
{
	if (!data->philosophers)
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free(data->fork);
		printf("Error: malloc philosophers failed\n");
		return (0);
	}
	return (1);
}
