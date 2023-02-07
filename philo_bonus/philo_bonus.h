/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:40:52 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/08 01:14:51 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_info
{
	int				id;
	int				num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_size;
	int				eat_finished;
	int				eat_count;
	long			start;
	long			last_time;
	t_moni			*moni;
	sem_t			forks;
}	t_info;

typedef struct s_moni
{
	int			die;
	pthread_t	thread;
}	t_moni;

// utils.c
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	print_philo(t_info *info,  char *str);
long	get_time(void);
void	pass_time(long wait_time, t_moni *moni);
// init.c
int		init_info(t_info *info, char **argv);
// thread.c
void	*monitoring(void *argv);
// share.c
void	change_finish(t_info *info);
int		check_fork(t_info *info, int id);
int		check_finish(t_info *info);
long	get_share(t_info *info, int flag);
#endif
