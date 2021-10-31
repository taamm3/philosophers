#include "philo.h"

void t_sleep(int t)
{
	long long time;

	time = milisec();
	while(1)
	{
		if(milisec() - time >= t)
			break;
		usleep(50);
	}
}

long long milisec() 
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int		ft_atoi(char *str)
{
	int i;
	int min;
	long num;

	i = 0;
	num = 0;
	min = 1;
	while (str[i] == ' ' || str[i] == '\t' ||
			str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			write(1,"Error\n",6);
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i++;
		if(num > 2147483647)
		{
			write(1,"Error\n",6);
			return (-1);
		}
	}
	if(str[i] != '\0')
	{
		write(1,"Error\n",6);
        return (-1);
	}
	return (num);
}
