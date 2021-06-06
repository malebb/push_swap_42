/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biggest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:32:30 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:33:12 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	first_or_second_biggest(t_nbr *stack_a, int *biggest_nbrs,
		t_nbr *first_nb)
{
	int		count;

	count = 0;
	while (stack_a)
	{
		if (!count || biggest_nbrs[0] < stack_a->value)
			biggest_nbrs[0] = stack_a->value;
		stack_a = stack_a->next;
		count = 1;
	}
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count && stack_a->value != biggest_nbrs[0])
		{
			biggest_nbrs[1] = stack_a->value;
			count = 1;
		}
		if (count && biggest_nbrs[1] < stack_a->value && stack_a->value
			!= biggest_nbrs[0])
			biggest_nbrs[1] = stack_a->value;
		stack_a = stack_a->next;
	}
}

int	*biggest_numbers(t_nbr *stack_a)
{
	int		*biggest_nbrs;
	t_nbr	*first_nb;
	int		count;

	first_nb = stack_a;
	biggest_nbrs = malloc(sizeof(int) * 3);
	if (!biggest_nbrs)
		return (0);
	first_or_second_biggest(stack_a, biggest_nbrs, first_nb);
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count && stack_a->value != biggest_nbrs[0]
			&& stack_a->value != biggest_nbrs[1])
		{
			biggest_nbrs[2] = stack_a->value;
			count = 1;
		}
		if (biggest_nbrs[2] < stack_a->value && stack_a->value
			!= biggest_nbrs[0] && stack_a->value != biggest_nbrs[1])
			biggest_nbrs[2] = stack_a->value;
		stack_a = stack_a->next;
	}
	return (biggest_nbrs);
}
