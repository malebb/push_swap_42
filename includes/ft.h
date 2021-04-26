#ifndef FT_H
# define FT_H
#include <stdlib.h>
#include <unistd.h>
char	*ft_strdup(const char *str);
int		ft_strlen(const char *str);
int		ft_isdigit(int c);
char	*ft_strcpy(char *dest, const char *src);
void	ft_putstr(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
#endif
