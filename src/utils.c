/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:19:01 by lsoghomo          #+#    #+#             */
/*   Updated: 2022/02/18 16:42:26 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libs/philo.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	v;

	s = 1;
	v = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		v = (v * 10) + (*str - 48);
		str++;
	}
	return (s * v);
}

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	return (0);
}

int	ft_print_status(char *str, t_data *data, int id)
{
	if (!data->terminate)
	{
		pthread_mutex_lock(&data->print);
		printf("%llu %d %s\n", get_time() - data->program_time, id, str);
		pthread_mutex_unlock(&data->print);
	}
	return (0);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
