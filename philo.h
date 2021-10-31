#ifndef PHILO_H
#define PHILO_H
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include <sys/time.h>
#include <unistd.h>

struct s_anun
{
	pthread_mutex_t *fork;
	pthread_mutex_t m;
	long long *last;
	int nbr_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int nbr_eat;
	int nbr_ph;
	long long t_start;
	int over;
}   anun;

typedef struct s_philo
{
	pthread_t philo;
}   t_philo;

long long    	milisec();
int		ft_atoi(char *str);
void 	*death(void *i);
void	t_sleep(int t);

#endif