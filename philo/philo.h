/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:40:52 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/07 22:40:53 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_size;
	int				eat_finished;
	int				finish;
	pthread_mutex_t	status;
	pthread_mutex_t	finish_check;
	pthread_mutex_t	print;
}	t_info;

typedef struct s_share
{
	int				*fork_status;
	pthread_mutex_t	*forks;
}	t_share;

typedef struct s_philo
{
	int			id;
	long		start;
	int			right;
	int			left;
	int			eat_count;
	long		last_time;
	pthread_t	thread;
	t_info		*info;
	t_share		*share;
}	t_philo;
// philo.c
int		free_thread(t_info *info, t_share *share, t_philo *philo, int result);
// utils.c
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	print_philo(t_info *info, t_philo *philo, char *str);
long	get_time(void);
void	pass_time(long wait_time, t_info *info);
// init.c
int		init_philo(t_info *info, t_share *share, t_philo **philo);
int		init_share(t_info *info, t_share *share);
int		init_info(t_info *info, t_share *share, char **argv);
// thread.c
void	*philo_loof(void *argv);
void	monitoring(t_info *info, t_philo *philo);
// share.c
void	change_finish(t_info *info);
int		check_fork(t_info *info, t_share *share, int id);
int		check_finish(t_info *info);
long	get_share(t_info *info, t_philo *philo, int flag);
#endif
