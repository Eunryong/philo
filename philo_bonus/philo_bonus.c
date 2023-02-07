/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:33:48 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/08 01:08:24 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_info *info, t_share *share, t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->status);
	i = 0;
	while (i < info->num)
		pthread_mutex_destroy(&share->forks[i++]);
	free(share->fork_status);
	free(share->forks);
	free(philo);
}

int	ft_philo(t_info *info, t_share *share, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		philo[i].last_time = get_time();
		if (pthread_create(&philo[i].thread, NULL, philo_loof, &philo[i]) == -1)
			return (5);
		i++;
	}
	monitoring(info, philo);
	i = 0;
	while (i < info->num)
		pthread_join(philo[i++].thread, NULL);
	free_thread(info, share, philo);
	return (0);
}

void	print_error(int flag)
{
	if (flag == 1)
	{
		ft_putendl_fd("invalid of number argument", 2);
		exit (0);
	}
	else if (flag == 2)
	exit (1);
}

int	main(int argc, char **argv)
{
	int		result;
	t_info	info;
	t_share	share;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (print_error(1));
	memset(&info, 0, sizeof(t_info));
	memset(&share, 0, sizeof(t_share));
	result = init_info(&info, &share, argv);
	if (result)
		return (print_error(result));
	result = init_philo(&info, &share, &philo);
	if (result)
		return (print_error(result));
	result = ft_philo(&info, &share, philo);
	if (result)
		return (print_error(result));
}
