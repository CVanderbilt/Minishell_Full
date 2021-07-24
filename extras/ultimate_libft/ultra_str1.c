#include "ultra_utils.h"

static int	ft_dgts(long int n)
{
	int	div;
	int	i;

	div = 1;
	i = 0;
	if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	if (n < 10)
		return (i + 1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			dgts;
	int			min;
	long int	n2;
	char		*p;

	dgts = ft_dgts(n);
	p = (char *)malloc(dgts + 1);
	if (!p)
		return (0);
	min = 0;
	if (n < 0)
		min = 1;
	p[0] = '-';
	p[dgts] = 0;
	n2 = n;
	if (n < 0)
		n2 *= -1;
	while (--dgts >= min)
	{
		p[dgts] = n2 % 10 + 48;
		n2 /= 10;
	}
	return (p);
}

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str++ <= '9')
		ret = *(str - 1) - 48 + 10 * ret;
	return (ret * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strfind(const char *str, char to_find)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == to_find)
			return (i);
	return (-1);
}
