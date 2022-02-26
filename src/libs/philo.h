/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoghomo <lsoghomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:19:24 by lsoghomo          #+#    #+#             */
/*   Updated: 2022/02/18 16:42:20 by lsoghomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include "colors.h"

struct	s_data;

typedef struct s_philo
{
	uint64_t		last_time_ate;
	bool			ate_enough;
	int				ind;
	int				left_fork;
	int				right_fork;
	int				times_ate;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	bool			terminate;
	pthread_t		check_state;
	pthread_t		philo_thread[255];
	pthread_mutex_t	forks[255];
	pthread_mutex_t	print;
	uint64_t		program_time;
	int				number_of_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				times_must_eat;
	t_philo			philos[255];
}					t_data;

uint64_t	get_time(void);
void		*ft_start(void *arg);
int			ft_init(t_data *data);
int			ft_join(t_data *data);
int			ft_isdigit(int arg);
int			ft_atoi(const char *str);
void		*check_status(void *arg);
void		check_eating(t_data *data);
int			store_data(t_data *data, char **args, int argc);
int			ft_print_status(char *str, t_data *data, int id);

#endif
