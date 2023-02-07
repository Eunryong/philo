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

#include "philo_bonus.h"

void	ft_philo(t_info *info, int id)
{
	info->id = id;
	if (pthread_create(&info->moni->thread, NULL, monitoring, &info) == -1)
		print_error(1);
	while (!info->moni->die)
	{
		if (info->eat_count == info->eat_size)
			exit (0);
		if (!philo_eating(info))
			continue ;
		print_philo(info, "is sleeping");
		pass_time(info->time_sleep, info->moni);
		print_philo(info, "is thinking");
	}
	pthread_join(&info->moni->thread, NULL);
	exit (0);
}

void	fork_philo(t_info *info)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < info->num)
	{
		pid = fork();
		if (pid < 0)
			print_error(1);
		if (pid == 0)
			ft_philo(info, i);
	}
	while (pid > 0)
		pid = wait(NULL);
	free_thread(info);
	return (0);
}

void	print_error(char *str, int flag)
{
	if (flag == 1)
	{
		ft_putendl_fd("invalid of number argument", 2);
		exit (1);
	}
	else
		perror(str);
	exit (1);
}

int	main(int argc, char **argv)
{
	int		result;
	t_info	info;
	t_moni	moni;

	if (argc != 5 && argc != 6)
		print_error(1);
	memset(&info, 0, sizeof(t_info));
	init_info(&info, argv);
	fork_philo(&info);
}
