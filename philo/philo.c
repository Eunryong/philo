/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:33:48 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/07 20:38:10 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_thread(t_info *info, t_share *share, t_philo *philo, int result)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->status);
	i = 0;
	while (i < info->num)
		pthread_mutex_destroy(&share->forks[i++]);
	if (share->fork_status)
		free(share->fork_status);
	if (share->forks)
		free(share->forks);
	if (philo)
		free(philo);
	return (result);
}

int	ft_philo(t_info *info, t_share *share, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num)
	{
		philo[i].last_time = get_time();
		if (pthread_create(&philo[i].thread, NULL, philo_loof, &philo[i]) == -1)
			return (free_thread(info, share, philo, 5));
		i++;
	}
	monitoring(info, philo);
	i = 0;
	while (i < info->num)
		pthread_join(philo[i++].thread, NULL);
	return (free_thread(info, share, philo, 0));
}

int	print_error(int result)
{
	if (result == 1)
		ft_putendl_fd("invalid of number argument", 2);
	else if (result == 2)
		ft_putendl_fd("invalid value", 2);
	else if (result == 3)
		ft_putendl_fd("mutex init error", 2);
	else if (result == 4)
		ft_putendl_fd("allocate error", 2);
	else if (result == 5)
		ft_putendl_fd("creat error", 2);
	return (result);
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
