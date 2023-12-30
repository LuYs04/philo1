/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:00:42 by tumolabs          #+#    #+#             */
/*   Updated: 2023/12/30 17:06:18 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, t_philo **ph)
{
	pthread_mutex_lock(&(*ph)->inf->print);
	pthread_mutex_lock(&(*ph)->inf->time);
	printf("%lld %d %s", get_time_in_ms(), (*ph)->philo_id + 1, str);
	pthread_mutex_unlock(&(*ph)->inf->time);
	pthread_mutex_unlock(&(*ph)->inf->print);
}

void	philos_are_more_than_1(t_philo **ph, int i)
{
	pthread_mutex_lock(&(*ph)->inf->fork[i]);
	print("has taken a fork\n", ph);
	print("is eating\n", ph);
	pthread_mutex_lock(&(*ph)->inf->time);
	(*ph)->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&(*ph)->inf->time);
	my_usleep((*ph)->inf->eat_time, ph);
	pthread_mutex_lock(&(*ph)->inf->meals[i]);
	((*ph)->meals_count)++;
	pthread_mutex_unlock(&(*ph)->inf->meals[i]);
	pthread_mutex_unlock(&(*ph)->inf->fork[i]);
}

void	eat(t_philo **ph)
{
	int	i;

	i = (*ph)->philo_id;
	if (i == 0)
		pthread_mutex_lock(&(*ph)->inf->fork[(*ph)->inf->nb_of_philos - 1]);
	else
		pthread_mutex_lock(&(*ph)->inf->fork[i - 1]);
	print("has taken a fork\n", ph);
	if ((*ph)->inf->nb_of_philos > 1)
		philos_are_more_than_1(ph, i);
	if (i == 0)
		pthread_mutex_unlock(&(*ph)->inf->fork[(*ph)->inf->nb_of_philos - 1]);
	else
		pthread_mutex_unlock(&(*ph)->inf->fork[i - 1]);
}

void	*philo_act(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	int	die_flag;
	if (ph->philo_id % 2 != 0)
		my_usleep(ph->inf->eat_time, &ph);
	while (1)
	{
		eat(&ph);
		print("is sleeping\n", &ph);
		my_usleep(ph->inf->sleep_time, &ph);
		print("is thinking\n", &ph);
		// pthread_mutex_lock(&ph->inf->time);
		// pthread_mutex_unlock(&ph->inf->time);
		die_flag = is_dying(ph);
		if (die_flag)
			break ;
		// pthread_mutex_unlock(&ph->inf->time);
		// if (is_dying(&ph))
		// 	break ;
	}
	return (0);
}
