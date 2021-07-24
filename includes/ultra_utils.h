#ifndef ULTRA_UTILS_H
# define ULTRA_UTILS_H

# include <unistd.h>
# include <stdlib.h>

/*
*			string related functions
*/
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int n);
char	*ft_strjoin(char *s1, char *s2, char c);
char	*ft_append(const char *s1, const char *s2);
char	*ft_itoa(int n);

unsigned ft_strlen(const char *str);

int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strfind(const char *str, char to_find);

/*
*			I/O related functions
*/
void	ft_putstr(const char *str);
void	ft_putstr_fd(int fd, const char *str);
void	ft_putnbr_fd(int fd, long long num);
int		get_next_line(char **line);

/*
*			Checks
*/
int		ft_is_digit(char c);
int		ft_is_printable(char c);

/*
*			Frees
*/
void	*ft_free(void *ptr);
void	*ft_close(int fd);
void	*ft_dummy(int n);

/*
*			Log
*/
int		ft_log(const char *str);
int		ft_logn(const char *str);
int		ft_nlog(long long int n);

#endif