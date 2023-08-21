/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:38:44 by ankinzin          #+#    #+#             */
/*   Updated: 2023/08/14 14:24:13 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy_mutex_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
}

void	ft_destroy_free(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->print);
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free (data->fork);
	free (data->philosophers);
}

void	ft_print_exit(char *str, int flag)
{
	printf("%s", str);
	exit (flag);
}

static int	len_number(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	else if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int number)
{
	int		len;
	long	num;
	char	*str;

	num = number;
	len = len_number(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	while (num > 0)
	{
		str[len--] = (48 + (num % 10));
		num /= 10;
	}
	return (str);
}
