/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:38:41 by ankinzin          #+#    #+#             */
/*   Updated: 2023/08/18 15:23:05 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	return (res * sign);
}

/* This func gets the current time in milliseconds using a precise clock*/
long long	ft_get_time(void)
{
	struct timeval	time;
	long long		time_in_milliseconds;

	gettimeofday(&time, NULL);
	time_in_milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_milliseconds);
}

long long	ft_abs_time(t_philo *root)
{
	return (ft_get_time() - root->data->t_init);
}

/* This func prints a message with the time ellapsed sinze a specific event
** alongside with the Philo's ID and a given message, we make sure to print
** philosopher at a time using a mutex, if all finishd eating or if any
** has died it stops printing*/
void	ft_print(t_philo *root, char *str)
{
	long long	time_ms;
	short	died;

	pthread_mutex_lock(&root->data->deaths);
	died = root->data->god.died;
	pthread_mutex_unlock(&root->data->deaths);

	time_ms = (ft_get_time() - root->data->t_init);
	pthread_mutex_lock(&root->data->print);
	if (root->data->god.all_ate || died)
	{
		pthread_mutex_unlock(&root->data->print);
		return ;
	}
	printf("%lld %d %s\n", time_ms, root->id, str);
	pthread_mutex_unlock(&root->data->print);
}
