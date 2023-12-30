/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:27:15 by tumolabs          #+#    #+#             */
/*   Updated: 2023/12/30 17:28:50 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	q;

	res = 0;
	q = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		q++;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (q == 1)
		res *= -1;
	return (res);
}

long long	get_time_in_ms(void)
{
	struct timeval			tv;
	static long long int	start;
	static int				count;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (count != 1)
	{
		start = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
		count = 1;
	}
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}

long long	my_usleep(int time, t_philo **ph)
{
	int			i;
	long long	a;

	i = 0;
	pthread_mutex_lock(&(*ph)->inf->time);
	a = get_time_in_ms();
	pthread_mutex_unlock(&(*ph)->inf->time);
	// pthread_mutex_lock(&(*ph)->inf->time);
	while (get_time_in_ms() - a < time)
		;
	// pthread_mutex_unlock(&(*ph)->inf->time);
	
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s_1;
	unsigned char	*s_2;
	size_t			i;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	while (s_1[i] && s_1[i] == s_2[i] && i < n)
		i++;
	if (i < n)
		return (s_1[i] - s_2[i]);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}
