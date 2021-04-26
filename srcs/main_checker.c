#include "checker.h" 

long long int	ft_atoi(char *nbr)
{
	long long int	nb;
	int				neg;
	int				i;

	i = 0;
	neg = 1;
	if (nbr[i] == '-')
	{
		i++;
		neg = -1;
	}
	nb = 0;
	while (nbr[i] != '\0')
	{
		nb *= 10;
		nb += nbr[i] - 48;
		i++;
	}
	return (nb * neg);
}

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
	(void)argv;
	return (TRUE);
}

t_nbr		*new_nbr(long long int nb)
{
	t_nbr		*nbr;

	if (!(nbr = malloc(sizeof(t_nbr) * (1))))
		return (NULL);
	nbr->value = (int)nb;
	nbr->next = NULL;
	return (nbr);
}

int			add_nbr(t_nbr **nbrs, long long int nb)
{
	t_nbr		*first_nb;	

	if (!(*nbrs))
	{
		if (!(*nbrs = new_nbr(nb)))
			return (0);
	}
	else
	{
		first_nb = *nbrs;
		while ((*nbrs)->next != 0)
			*nbrs = (*nbrs)->next;
		if (!((*nbrs)->next = new_nbr(nb)))
			return (0);
		*nbrs = first_nb;
	}

	return (1);
}

t_nbr		*stock_numbers(char *argv[])
{
	int				i;
	t_nbr			*nbrs;
	long long int	nb;

	i = 1;
	nbrs = NULL;
	while (argv[i] != NULL)
	{
		nb = ft_atoi(argv[i]);
		if (nb < -2147483648 || nb > 2147483647)
			return  (NULL);	
		if (!add_nbr(&nbrs, nb))
			return (NULL);
		i++;
	}
	return (nbrs);
}

t_nbr		*check_args(char *argv[])
{
	t_nbr		*nbrs;

	if (!only_numbers(argv))
		return (NULL);
	if (!(nbrs = stock_numbers(argv)))
		return (NULL);
	if (!check_overflow(argv))
		return (NULL);
	if (!check_duplicates(argv))
		return (NULL);
	return (nbrs);
}

int		main(int argc, char *argv[])
{
	(void)argc;
	t_nbr		*nbrs;

	if (argc < 2)
		return (1);
	if (!(nbrs = check_args(argv)))
	{
		ft_putstr("Error\n");
		return (1);
	}
	while (nbrs)
	{
		printf("nb = %d\n", nbrs->value);
		nbrs = nbrs->next;
	}
	return (0);
}
