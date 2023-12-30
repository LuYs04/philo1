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
	// printf("last_meal of %d ====== %d\n", i, (*ph)->last_meal);
	pthread_mutex_unlock(&(*ph)->inf->time);
	pthread_mutex_lock(&(*ph)->inf->wait[i]);
	my_usleep((*ph)->inf->eat_time);
	pthread_mutex_unlock(&(*ph)->inf->wait[i]);
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
	if (ph->philo_id % 2 != 0)
	{
		pthread_mutex_lock(&ph->inf->wait[ph->philo_id]);
		my_usleep(ph->inf->eat_time);
		pthread_mutex_unlock(&ph->inf->wait[ph->philo_id]);
	}
	while (!is_dying(&ph))
	{
		eat(&ph);
		print("is sleeping\n", &ph);
		pthread_mutex_lock(&ph->inf->wait[ph->philo_id]);
		my_usleep(ph->inf->sleep_time);
		pthread_mutex_unlock(&ph->inf->wait[ph->philo_id]);
		print("is thinking\n", &ph);
	}
	return (0);
}
