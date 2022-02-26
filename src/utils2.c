/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:54:44 by lsoghomo          #+#    #+#             */
/*   Updated: 2022/02/26 15:59:06 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/philo.h"

int	ft_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		if (pthread_create(&data->philo_thread[i], NULL,
				&ft_start, (void *)&data->philos[i]) != 0)
		{
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->check_state, NULL,
			&check_status, (void *)data) != 0)
	{
		return (1);
	}
	return (0);
}

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philo_thread[i], NULL) != 0)
		{
			usleep(100);
			return (2);
		}
		i++;
	}
	if (pthread_join(data->check_state, NULL) != 0)
	{
		return (2);
	}
	return (0);
}
