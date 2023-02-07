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

#include "philo.h"

void	monitoring(t_info *info, t_philo *philo)
{
	int		tmp;
	int		i;
	long	now;

	while (!check_finish(info))
	{
		tmp = (int)get_share(info, 0, 0);
		if (info->eat_size && info->num == tmp)
		{
			change_finish(info);
			break ;
		}
		i = -1;
		while (++i < info->num)
		{
			now = get_share(info, &philo[i], 1);
			if (now >= info->time_die)
			{
				print_philo(info, &philo[i], "died");
				change_finish(info);
				break ;
			}
		}
	}
}

int	philo_eat(t_info *info, t_share *share, t_philo *philo)
{
	if (check_fork(info, share, philo->id))
	{
		pthread_mutex_lock(&(share->forks[philo->left]));
		print_philo(info, philo, "has token a fork");
		if (info->num != 1)
		{
			pthread_mutex_lock(&(share->forks[philo->right]));
			print_philo(info, philo, "has token a fork");
			print_philo(info, philo, "is eating");
			pthread_mutex_lock(&info->status);
			philo->last_time = get_time();
			philo->eat_count++;
			share->fork_status[philo->right] = 0;
			share->fork_status[philo->left] = 0;
			pthread_mutex_unlock(&info->status);
			pass_time((long)info->time_eat, info);
			pthread_mutex_unlock(&(share->forks[philo->right]));
			pthread_mutex_unlock(&(share->forks[philo->left]));
			return (1);
		}
		pthread_mutex_unlock(&(share->forks[philo->left]));
		return (0);
	}
	return (0);
}

void	*philo_loof(void *argv)
{
	t_philo	*philo;
	t_info	*info;
	t_share	*share;

	philo = argv;
	info = philo->info;
	share = philo->share;
	if (philo->id % 2)
		usleep(1000);
	while (!check_finish(info))
	{
		if (info->eat_size == philo->eat_count)
		{
			pthread_mutex_lock(&info->status);
			info->eat_finished++;
			pthread_mutex_unlock(&info->status);
			break ;
		}
		if (!philo_eat(info, share, philo))
			continue ;
		print_philo(info, philo, "is sleeping");
		pass_time((long)info->time_sleep, info);
		print_philo(info, philo, "is thinking");
	}
	return (0);
}
