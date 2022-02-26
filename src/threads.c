/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:18:51 by lsoghomo          #+#    #+#             */
/*   Updated: 2022/02/26 16:28:39 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].last_time_ate = gt();
		data->philos[i].ind = i;
		data->philos->ate_enough = false;
		data->philos[i].data = data;
		data->philos->times_ate = 0;
		if (i == 0)
			data->philos[i].left_fork = data->number_of_philos - 1;
		else
			data->philos[i].left_fork = i - 1;
		data->philos[i].right_fork = i;
		i++;
	}
}

int	check_num(char **arg, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (arg[i][j] == '0')
			return (1);
		while (arg[i][j] != '\0')
		{
			if (!ft_isdigit(arg[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	store_data(t_data *data, char **args, int argc)
{
	data->terminate = false;
	if (check_num(args, argc))
		return (1);
	data->number_of_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(args[5]);
	else
		data->times_must_eat = -1;
	init_philos(data);
	data->p_t = gt();
	return (0);
}

void	check_eating(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->number_of_philos)
	{
		if (data->philos[i].times_ate >= data->times_must_eat)
		{
			if (!data->philos[i].ate_enough)
				data->philos[i].ate_enough = true;
			else
				count++;
		}
		i++;
	}
	if (count == data->number_of_philos)
		data->terminate = true;
}

void	*check_status(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!data->terminate)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			if (data->philos[i].last_time_ate
				+ data->time_to_die < gt())
			{
				ft_print_status("died", data, data->philos[i].ind + 1, RED);
				data->terminate = true;
				pthread_mutex_unlock(&data->forks[data->philos[i].left_fork]);
				break ;
			}
			i++;
		}
		if (data->times_must_eat != -1)
			check_eating(data);
	}
	return (0);
}
