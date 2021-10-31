#include "philo.h"

void *death(void *i)
{
	int index = *((int *)i);
	while(1)
	{
		if(milisec() - anun.t_start - anun.last[index - 1] > anun.t_die)
		{
			pthread_mutex_lock(&anun.m);
			anun.over = 1;
			printf("%lld %d died\n", milisec() - anun.t_start, index);
			return (0);
		}
	}
}

void	*check()
{
	while (1)
	{
		if (anun.over)
			return (0);
	}
}

void *start(void *i)
{
	pthread_t t;
	int j = 0;
	int n = *((int *)i) + 1;
	pthread_create(&t, NULL, death, &n);
	if (n % 2 && n != anun.nbr_philo)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&anun.m);
		if(!anun.over)
		printf("%lld %d is thinking\n", milisec() - anun.t_start, n);
		pthread_mutex_unlock(&anun.m);
		pthread_mutex_lock(&anun.fork[n - 1]);
		pthread_mutex_lock(&anun.m);
		if(!anun.over)
		printf("%lld %d has taken a fork\n", milisec() - anun.t_start, n);
		pthread_mutex_unlock(&anun.m);
		if (n == anun.nbr_philo)
			pthread_mutex_lock(&anun.fork[0]);
		else
			pthread_mutex_lock(&anun.fork[n]);
		pthread_mutex_lock(&anun.m);
		if(!anun.over)
		printf("%lld %d has taken a fork\n", milisec() - anun.t_start, n);
		if(!anun.over)
		printf("%lld %d is eating\n", milisec() - anun.t_start, n);
		pthread_mutex_unlock(&anun.m);
		j++;
		if (j == anun.nbr_eat)
		anun.nbr_ph++;
		if (anun.nbr_ph == anun.nbr_philo)
		anun.over = 1;
		anun.last[n - 1] = milisec() - anun.t_start;
		t_sleep(anun.t_eat);
		pthread_mutex_unlock(&anun.fork[n - 1]);
		if (n == anun.nbr_philo)
			pthread_mutex_unlock(&anun.fork[0]);
		else
			pthread_mutex_unlock(&anun.fork[n]);
		pthread_mutex_lock(&anun.m);
		if(!anun.over)
		printf("%lld %d is sleeping\n", milisec() - anun.t_start, n);
		pthread_mutex_unlock(&anun.m);
		t_sleep(anun.t_sleep);
	}
	return (0);
}

void init(int argc, char **argv)
{
	anun.nbr_philo = ft_atoi(argv[1]);
	anun.t_die = ft_atoi(argv[2]);
	anun.t_start = milisec();
	anun.t_eat = ft_atoi(argv[3]);
	anun.t_sleep = ft_atoi(argv[4]);
	anun.over = 0;
	if (argc == 6)
		anun.nbr_eat = ft_atoi(argv[5]);
	else
		anun.nbr_eat = -3; 
}

int main(int argc, char **argv)
{
	t_philo *t;
	pthread_t ch;
	int i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: argument\n");
		return (1);
	}
	init(argc, argv);
	if (anun.nbr_philo == 0)
	{
		printf("Error: no philosopher\n");
		return (1);
	}
	if (anun.nbr_philo == -1 || anun.t_die == -1 || anun.t_eat == -1 || anun.t_sleep == -1 || anun.nbr_eat == -1)
		return (1);
	if (anun.nbr_philo == 1)
	{
		printf("%lld 1 is thinking\n", milisec() - anun.t_start);
		t_sleep(anun.t_die);
		printf("%lld 1 died\n", milisec() - anun.t_start);
		return (0);
	}
	int a[anun.nbr_philo];
	while (i < anun.nbr_philo)
	{
		a[i] = i;
		i++;
	}
	if (!(t = malloc(sizeof(t_philo) * anun.nbr_philo)))
	{
		printf("Error: can't malloc\n");
		return (1);
	}
	if (!(anun.fork = malloc(sizeof(pthread_mutex_t) * anun.nbr_philo)))
	{
		printf("Error: can't malloc\n");
		return (1);
	}
	if (!(anun.last = malloc(sizeof(long long) * anun.nbr_philo)))
	{
		printf("Error: can't malloc\n");
		return (1);
	}
	i = 0;
	while (i < anun.nbr_philo)
	{
		anun.last[i] = 0;
		i++;
	}
	pthread_mutex_init(&anun.m, NULL);
	pthread_create(&ch, NULL, check, NULL);
	i = 0;
	while (i < anun.nbr_philo)
	{
		pthread_mutex_init(&anun.fork[i], NULL);
		pthread_create(&t[i].philo, NULL, start, &a[i]);
		i++;
	}
	pthread_join(ch, NULL);
	i = 0;
	while (i < anun.nbr_philo)
	{
		pthread_mutex_unlock(&anun.fork[i]);
		pthread_mutex_destroy(&anun.fork[i]);
		i++;
	}
	pthread_mutex_destroy(&anun.m);
	free(t);
	free(anun.fork);
	free(anun.last);
	return (0);
}
