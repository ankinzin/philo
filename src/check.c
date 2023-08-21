/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:44 by ankinzin          #+#    #+#             */
/*   Updated: 2023/08/18 15:21:32 by ankinzin         ###   ########.fr       */
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

/* this func ensures that the simulation responds to the philosophers
** activities appropriately, monitoring for potential deaths and
** tracking meals completion*/
static int	ft_god_complement(t_philo *root)
{
	if ((ft_get_time() - root->last_meal) > root->data->t_die)
	{
		ft_print(root, "died");
		pthread_mutex_lock(&root->data->deaths);
		root->data->god.died = 1;
		pthread_mutex_unlock(&root->data->deaths);
		return (1);
	}
	if ((root->num_of_meals >= root->data->n_must_eat)
		&& root->data->n_must_eat != -1)
		root->data->god.num_of_meals++;
	if (root->data->god.num_of_meals == root->data->num_of_philo)
	{
		ft_print(root, "All philosophers ate enough\n");
		root->data->god.all_ate = 1;
		return (1);
	}
	return (0);
}

/* This func acts like the supervisor of the simulation, ensuring that
** any critical events are detected and acted upon promptly*/
void	ft_god(t_data *data)
{
	int		i;
	t_philo	*root;

	while (1)
	{
		i = -1;
		data->god.num_of_meals = 0;
		while (++i < data->num_of_philo)
		{
			root = &data->philosophers[i];
			if (ft_god_complement(root))
				return ;
		}
	}
}
