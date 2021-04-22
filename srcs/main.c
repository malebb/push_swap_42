#include "checker.h"

int		main(void)
{
	char	*line;
	int		ret;

	while ((ret = gnl(&line)) == 1)
	{
		printf("ret = %d\n", ret);
		printf("l: %s\n", line);
	}
	printf("ret = %d\n", ret);
	printf("l: %s\n", line);
	return (0);
}
