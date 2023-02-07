/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:33:46 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/08 01:14:41 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_info(t_info *info, char **argv)
{
	t_moni	moni;
	int		ret;

	memset(&moni, 0, sizeof(t_moni));	
	info->num = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->moni = malloc(sizeof(t_moni));
	memset(info->moni, 0, sizeof(t_moni));
	if (info->num < 1 || info->time_die < 0 || info->time_eat < 0 \
		|| info->time_sleep < 0)
		return (2);
	if (argv[5])
	{
		info->eat_size = ft_atoi(argv[5]);
		if (info->eat_size < 0)
			return (2);
	}
	sem_init(&info->forks, 0, info->num);
	return (0);
}
