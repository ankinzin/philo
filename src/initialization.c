/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:41 by ankinzin          #+#    #+#             */
/*   Updated: 2023/08/18 15:30:26 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* This func takes the CLI and converts them into meaningful values, and sets
** up the data needed for the program to run, it also checks if the data is
** valid and returns the result of the check */
int	ft_initialize_data(t_data *data, int argc, char **argv)
{
	short	i;

	i = 1;
	data->n_must_eat = -1;
	data->num_of_philo = ft_atoi(argv[i++]);
	data->t_die = ft_atoi(argv[i++]);
	data->t_eat = ft_atoi(argv[i++]);
	data->t_sleep = ft_atoi(argv[i++]);
	if (argv[i])
		data->n_must_eat = ft_atoi(argv[i]);
	return (ft_check_data(data, argc));
}

int	ft_initialize_print(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL))
	{
		printf("Error: mutex init failed\n");
		return (0);
	}

	if (pthread_mutex_init(&data->deaths, NULL))
	{
		printf("Error: mutex init failed\n");
		return (0);
	}
	return (1);
}

/* This func allocates memory for mutexes, init mutexes for each fork
** and handles cleanup in case of any errors during initialization*/
int	ft_initialize_fork(t_data *data)
{
	int	i;
	int	j;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->fork)
	{
		printf("Error: malloc fork failed\n");
		return (0);
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			pthread_mutex_destroy(&data->print);
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&data->fork[j]);
			free(data->fork);
			printf("Error: mutex init (fork) failed\n");
			return (0);
		}
	}
	return (1);
}

/* This func allocates memory of a philosopher strctures, sets up their data
** and prepares the necessary info for each philosopher to start their
** actions at the dining table*/
int	ft_initialize_philo(t_data *data)
{
	int	i;

	data->philosophers = (t_philo *)malloc(sizeof
			(t_philo) * data->num_of_philo);
	if (!data->philosophers)
	{
		pthread_mutex_destroy(&data->print);
		ft_destroy_mutex_fork(data);
		free (data->fork);
		printf("Error: malloc philosophers failed\n");
		return (0);
	}
	memset(data->philosophers, 0, sizeof
		(t_philo) * data->num_of_philo);
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].num_of_meals = 0;
		data->philosophers[i].left_fork = &data->fork[i];
		data->philosophers[i].right_fork = &data->fork[(i + 1)
			% data->num_of_philo];
		data->philosophers[i].data = data;
	}
	return (1);
}

/* This func structures the setup execution, and management of the philosopher
** simulation, ensures proper thread creation, monitoring an synchronization */
int	ft_initialize_simulation(t_data *data)
{
	int	i;

	data->god.all_ate = 0;
	data->god.died = 0;
	i = -1;
	data->t_init = ft_get_time();
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philosophers[i].thread,
				NULL, ft_action, &data->philosophers[i]))
		{
			ft_destroy_free(data);
			printf("Error: Simulation Failed \n");
			return (0);
		}
		// usleep(SPAWN_RATE * 1000);
	}
	ft_god(data);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philosophers[i].thread, NULL);
	return (1);
}
