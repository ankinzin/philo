/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:34:41 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/02 17:52:50 by ankinzin         ###   ########.fr       */
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
	data->all_ate = 0;
	data->death_cause = false;
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

	data->philosophers = (t_philo *)malloc
		(sizeof(t_philo) * data->num_of_philo);
	if (!ft_safety_check (data))
		return (1);
	memset(data->philosophers, 0, sizeof(t_philo) * data->num_of_philo);
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal = data->t_init;
		data->philosophers[i].left_fork.m_fork = &data->fork[i];
		data->philosophers[i].left_fork.id = i + 1;
		data->philosophers[i].right_fork.m_fork
			= &data->fork[(i + 1) % data->num_of_philo];
		data->philosophers[i].right_fork.id
			= (i + 1) % data->num_of_philo + 1;
		data->philosophers[i].data = data;
		data->philosophers[i].died = 0;
		data->philosophers[i].num_of_meals = data->n_must_eat;
		if (!ft_initialize_philo_mtx(data, i))
			return (0);
	}
	return (1);
}

/* This func structures the setup execution, and management of the philosopher
** simulation, ensures proper thread creation, monitoring an synchronization */
int	ft_initialize_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->all_ate = 0;
	data->death_cause = false;
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philosophers[i].thread,
				NULL, ft_action, &data->philosophers[i]))
		{
			ft_destroy_free(data);
			printf("Error: Simulation Failed \n");
			return (0);
		}
	}
	pthread_create(&monitor, NULL, ft_god, data);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_join(data->philosophers[i].thread, NULL);
	pthread_join(monitor, NULL);
	if (data->death_cause)
		printf("%lld %d is dead\n", data->dead_at, data->dead_philo);
	return (1);
}
