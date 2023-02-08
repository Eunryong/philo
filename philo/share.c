/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:26:20 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/07 18:36:41 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_share(t_info *info, t_philo *philo, int flag)
{
	long	ret;

	pthread_mutex_lock(&info->status);
	if (!flag)
		ret = info->eat_finished;
	else
		ret = get_time() - philo->last_time;
	pthread_mutex_unlock(&info->status);
	return (ret);
}

void	change_finish(t_info *info)
{
	pthread_mutex_lock(&info->finish_check);
	info->finish = 1;
	pthread_mutex_unlock(&info->finish_check);
}

int	check_fork(t_info *info, t_share *share, int id)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&info->status);
	if (!share->fork_status[id] && !share->fork_status[(id + 1) % info->num])
	{
		share->fork_status[id] = 1;
		share->fork_status[(id + 1) % info->num] = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&info->status);
	return (ret);
}

int	check_finish(t_info *info)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&info->finish_check);
	if (info->finish)
		ret = 1;
	pthread_mutex_unlock(&info->finish_check);
	return (ret);
}
