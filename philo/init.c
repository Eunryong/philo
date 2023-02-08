/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:33:46 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/08 02:16:33 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_info *info, t_share *share, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->num);
	if (!*philo)
		return (free_thread(info, share, 0, 4));
	i = -1;
	while (++i < info->num)
	{
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % info->num;
		(*philo)[i].eat_count = 0;
		(*philo)[i].start = get_time();
		(*philo)[i].info = info;
		(*philo)[i].share = share;
	}
	return (0);
}

int	init_share(t_info *info, t_share *share)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->finish_check, NULL) == -1)
		return (3);
	if (pthread_mutex_init(&info->print, NULL) == -1)
		return (3);
	if (pthread_mutex_init(&info->status, NULL) == -1)
		return (3);
	share->fork_status = malloc(sizeof(pthread_mutex_t) * info->num);
	if (!share->fork_status)
		return (4);
	memset(share->fork_status, 0, sizeof(int) * info->num);
	share->forks = malloc(sizeof(pthread_mutex_t) * info->num);
	if (!share->forks)
		return (4);
	i = -1;
	while (++i < info->num)
	{
		if (pthread_mutex_init(&share->forks[i], NULL) == -1)
			return (4);
	}
	return (0);
}

int	init_info(t_info *info, t_share *share, char **argv)
{
	int	ret;

	info->num = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->num < 1 || info->time_die < 0 || info->time_eat < 0 \
		|| info->time_sleep < 0)
		return (2);
	if (argv[5])
	{
		info->eat_size = ft_atoi(argv[5]);
		if (info->eat_size < 1)
			return (2);
	}
	ret = init_share(info, share);
	if (ret)
		return (free_thread(info, share, 0, ret));
	return (0);
}
