/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:44 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/02 16:57:46 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* This func is responsible for checking the input data if it it correct
** ensuring every philosopher simulation can be properly executed with
** the provided parameters*/
int	ft_check_data(t_data *data, int argc)
{
	if (data->num_of_philo < 1 || data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (data->n_must_eat < 0 && argc == 6))
	{
		if (data->num_of_philo < 1)
			printf("Error: number of philosophers must be greater than 0\n");
		else if (data->t_die < 0)
			printf("Error: time to die must be greater than 0\n");
		else if (data->t_eat < 0)
			printf("Error: time to eat must be greater than 0\n");
		else if (data->t_sleep < 0)
			printf("Error: time to sleep must be greater than 0\n");
		else
			printf("Error: num of times each philo must eat must be > than 0\n");
		return (0);
	}
	return (1);
}

int	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	return (1);
}

int	ft_check_is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0 && argv[i][j] == '-')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Arguments must be numbers\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_count_meals(t_philo *root)
{
	pthread_mutex_lock(&root->mtx_meal);
	if (root->num_of_meals == 0)
	{
		root->data->n_must_eat -= 1;
		root->num_of_meals -= 1;
	}
	pthread_mutex_unlock(&root->mtx_meal);
}

/* This func acts like the supervisor of the simulation, ensuring that
** any critical events are detected and acted upon promptly*/
void	*ft_god(void *in_data)
{
	int		i;
	t_data	*data;

	data = (t_data *)in_data;
	while (1)
	{
		i = -1;
		data->currtime = ft_get_time();
		while (++i < data->num_of_philo)
		{
			ft_count_meals(&data->philosophers[i]);
			if (ft_god_complement(&data->philosophers[i]))
				return (NULL);
		}
		if (data->n_must_eat == 0)
		{
			ft_print(&data->philosophers[i], "HOWWWWWWWWWW");
			return (NULL);
		}
	}
	return (NULL);
}
