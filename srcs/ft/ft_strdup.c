#include "ft.h"
char	*ft_strdup(const char *str)
{
	int		size_str;
	int		i;
	char	*dup;

	size_str = ft_strlen(str);
	if (!(dup = malloc(sizeof(char) * (size_str + 1))))
		return (NULL);
	i = 0;
	while (i < size_str)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
