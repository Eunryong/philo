/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 04:31:59 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/07 05:10:02 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_philo(t_info *info, char *str)
{
	long	now;

	if (!info->moni->die)
	{
		now = get_time() - info->start;
		printf("%ld %d %s\n", now, info->id + 1, str);
	}
}

void	pass_time(long wait_time, t_moni *moni)
{
	long	start;
	long	now;

	start = get_time();
	while (!moni->die)
	{
		now = get_time();
		if (now - start >= wait_time)
			break ;
		usleep(100);
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
