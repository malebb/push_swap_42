#include "checker.h"

int		check_duplicates(char *argv[])
{
	(void)argv;
	return (1);
}

int		only_numbers(char *argv[])
{
	int		i;
	int		j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]) && !(argv[i][j] == '-' && j == 0))
				return (FALSE);
			if (argv[i][j] == '-' && argv[i][j + 1] == '\0')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int		check_overflow(char *argv[])
{
	return (TRUE);
}

t_nbr		*check_args(char *argv[])
{
	t_nbr		*nbrs;

	if (!only_numbers(argv))
		return (NULL);
	nbbr
	if (!check_overflow(argv))
		return (NULL);
	if (!check_duplicates(argv))
		return (NULL);
	return (nbrs);
}

int		main(int argc, char *argv[])
{
	(void)argc;
	if (!check_args(argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	return (0);
}
