/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:18:53 by lsoghomo          #+#    #+#             */
/*   Updated: 2022/02/18 16:42:23 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libs/philo.h"

void	ft_usleep(uint64_t time)
{
	uint64_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(50);
}

void	mutex_locks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_print_status("has taken a fork", philo->data, philo->ind + 1);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_print_status("has taken a fork", philo->data, philo->ind + 1);
	ft_print_status("is eating", philo->data, philo->ind + 1);
	ft_usleep(philo->data->time_to_eat);
	philo->times_ate++;
	philo->last_time_ate = get_time();
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	ft_print_status("is sleeping", philo->data, philo->ind + 1);
	ft_usleep(philo->data->time_to_sleep);
	ft_print_status("is thinking", philo->data, philo->ind + 1);
}

void	*ft_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ind % 2 == 0)
		usleep(100);
	while (!philo->data->terminate)
	{
		mutex_locks(philo);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("%sError: Wrong number of parametres%s\n", RED, RESET);
		return (1);
	}
	if (store_data(&data, argv, argc))
	{
		printf("%sError: Wrong input parametre(s)%s\n", RED, RESET);
		return (1);
	}
	ft_init(&data);
	ft_join(&data);
	return (0);
}
