/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:17:01 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/07 18:37:39 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *argv)
{
	t_info	*info;
	long	now;
	int		i;

	info = argv;
	while (!info->moni->die)
	{
		if (info->eat_size && info->eat_size == info->eat_count)
		{
			info->moni->die = 1;
			break ;
		}
		i = -1;
		while (++i < info->num)
		{
			now = get_time - info->last_time;
			if (now >= info->time_die)
			{
				print_philo(info, "died");
				info->moni->die = 1;
			}
		}
	}
	return (0);
}

int	philo_eat(t_info *info)
{
	sem_wait(&info->forks);
	print_philo(info, "has token a fork");
	if (info->num != 1)
	{
		sem_wait(&info->forks);
		print_philo(info, "has token a fork");
		print_philo(info, "is eating");
		info->last_time = get_time();
		info->eat_count++;
		pass_time((long)info->time_eat, info);
		sem_post(&info->forks);
		sem_post(&info->forks);
		return (1);
	}
	sem_post(&info->forks);
	return (0);
}
