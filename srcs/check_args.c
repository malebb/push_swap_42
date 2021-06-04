/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:38:45 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/03 13:52:41 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	only_numbers(char *argv[])
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

static int	check_duplicates(t_nbr *nbr)
{
	t_nbr		*first_nbr;
	t_nbr		*nbr_passed;

	first_nbr = nbr;
	nbr_passed = nbr;
	while (nbr)
	{
		while (nbr_passed != nbr)
		{
			if (nbr_passed->value == nbr->value)
				return (0);
			nbr_passed = nbr_passed->next;
		}
		nbr_passed = first_nbr;
		nbr = nbr->next;
	}
	return (1);
}

t_nbr	*check_args(char *argv[])
{
	t_nbr		*stack_a;

	if (!only_numbers(argv))
		return (NULL);
	stack_a = stock_numbers(argv);
	if (!stack_a)
		return (NULL);
	if (!check_duplicates(stack_a))
	{
		free_stack(&stack_a);
		return (NULL);
	}
	return (stack_a);
}
