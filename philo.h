/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:19:15 by tumolabs          #+#    #+#             */
/*   Updated: 2023/12/30 17:25:41 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_info
{
	int				nb_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nb_of_meals;
	int				died;
	pthread_mutex_t	die;
	pthread_mutex_t	time;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*meals;
}				t_info;

typedef struct s_philo
{
	int			philo_id;
	int			last_meal;
	int			meals_count;
	pthread_t	philo;
	t_info		*inf;
}				t_philo;

typedef struct s_data
{
	t_info	*info;
	t_philo	*philos;
}				t_data;

long long	my_usleep(int time, t_philo **ph);
int			check(t_data *data);
int			ft_strlen(char *str);
long long	get_time_in_ms(void);
int			does_eat(t_philo *ph);
void		*philo_act(void *arg);
int			is_dying(t_philo *ph);
int			ft_atoi(const char *str);
int			init_data(t_data **data);
int			do_they_eat(t_data *data);
int			init_mutexes(t_data **dt);
int			join_threads(t_data **data);
int			create_threads(t_data **data);
void		print(char *str, t_philo **ph);
int			init_args(int argc, char **argv, t_data **data);
int			init_args(int argc, char **argv, t_data **data);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
