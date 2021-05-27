/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:39:21 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/18 11:40:18 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_nbr	*new_nbr(long long int nb)
{
	t_nbr		*nbr;

	if (!(nbr = malloc(sizeof(t_nbr) * (1))))
		return (NULL);
	nbr->value = (int)nb;
	nbr->next = NULL;
	return (nbr);
}

static int		add_nbr(t_nbr **nbrs, long long int nb)
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

t_nbr			*stock_numbers(char *argv[])
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
			return (NULL);
		if (!add_nbr(&nbrs, nb))
			return (NULL);
		i++;
	}
	return (nbrs);
}

int				count_nbr(t_nbr *nbrs)
{
	int		count;

	count = 0;
	while (nbrs)
	{
		count++;
		nbrs = nbrs->next;
	}
	return (count);
}

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
