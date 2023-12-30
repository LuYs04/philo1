/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:30 by tumolabs          #+#    #+#             */
/*   Updated: 2023/12/30 17:29:14 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argc < 5 || argc > 6
				|| !(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("ERROR: Invalid arguments!");
				return (1);
			}
		}
		if (ft_strlen(argv[i]) >= 10
			&& ft_strncmp(argv[i], "2147483647", 10))
		{
			printf("ERROR: Too big arguments!");
			return (1);
		}
	}
	return (0);
}

void	clear_data(t_data **data)
{
	int	i;

	i = -1;
	while (++i < (*data)->info->nb_of_philos)
	{
		pthread_mutex_destroy(&(*data)->info->fork[i]);
		pthread_mutex_destroy(&(*data)->info->meals[i]);
	}
	pthread_mutex_destroy(&(*data)->info->print);
	pthread_mutex_destroy(&(*data)->info->time);
	pthread_mutex_destroy(&(*data)->info->die);
}

int	init_data(t_data **data)
{
	if (init_mutexes(data))
		return (1);
	if (create_threads(data))
		return (1);
	if (join_threads(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("ERROR: Malloc error!");
		return (1);
	}
	if (!parsing(argc, argv))
	{
		if (init_args(argc, argv, &data))
			return (1);
		if (init_data(&data))
		{
			clear_data(&data);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}
