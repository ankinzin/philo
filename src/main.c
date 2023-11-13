/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:35:13 by ankinzin          #+#    #+#             */
/*   Updated: 2023/09/02 16:57:44 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!ft_check_argc(argc) || !ft_check_is_num(argv))
		return (0);
	if (!ft_initialize_data(&data, argc, argv))
		return (0);
	if (data.num_of_philo == 1)
	{
		printf("%d philo %d has taken a fork\n", 1, 1);
		printf("%lld philo %d died\n", data.t_die, 1);
		return (0);
	}
	if (!ft_initialize_print(&data) || !ft_initialize_fork(&data))
		return (0);
	data.t_init = ft_get_time();
	if (!ft_initialize_philo(&data))
		return (0);
	if (!ft_initialize_simulation(&data))
		return (0);
	ft_destroy_free(&data);
	return (0);
}
