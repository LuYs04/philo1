/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:25:49 by tumolabs          #+#    #+#             */
/*   Updated: 2023/12/30 17:26:49 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dying(t_philo *ph)
{
	int	tmp;

	pthread_mutex_lock(&ph->inf->time);
	tmp = get_time_in_ms() - ph->last_meal;
	printf("%d, %lld, %d, |||| %d\n", ph->philo_id + 1, get_time_in_ms(), ph->last_meal, tmp);
	pthread_mutex_unlock(&ph->inf->time);
	if (tmp >= ph->inf->die_time)
	{
		pthread_mutex_lock(&ph->inf->die);
		ph->inf->died = 1;
		pthread_mutex_unlock(&ph->inf->die);
		print("died.\n", &ph);
		return (1);
	}
	return (0);
}

int	do_they_eat(t_data *dt)
{
	int	i;
	int	count;

	i = 0;
	while (i < dt->info->nb_of_philos)
	{
		pthread_mutex_lock(&dt->info->meals[i]);
		count = dt->philos[i].meals_count;
		pthread_mutex_unlock(&dt->info->meals[i]);
		if (count < dt->info->nb_of_meals)
			break ;
		i++;
	}
	if (i == dt->info->nb_of_philos)
		return (1);
	return (0);
}
