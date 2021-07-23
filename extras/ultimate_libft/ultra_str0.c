#include "ultra_utils.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	ret = (char *)malloc(i + 1);
	if (!ret)
		return (0);
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char	*ft_strndup(const char *str, int n)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (len > n)
		len = n;
	i = -1;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (0);
	while (str[++i] && i < len)
		ret[i] = str[i];
	ret[len] = 0;
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2, char c)
{
	char	*ret;

	ret = ft_append(s1, s2);
	if (c == 'L' || c == 'B')
		free (s1);
	if (c == 'R' || c == 'B')
		free (s2);
	return (ret);
}

char	*ft_append(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*ret;
	int		error;

	error = 0;
	if (!s1 || !s2)
		return (0);
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		error = 1;
	i = -1;
	j = -1;
	while (s1[++i] && !error)
		ret[i] = s1[i];
	while (s2[++j] && !error)
		ret[i + j] = s2[j];
	if (!error)
		ret[i + j] = 0;
	return (ret);
}

unsigned int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
