/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:36:14 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:37:10 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	size_stack(t_nbr *stack)
{
	int		size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

t_algo	*rotate_back(int rotation, t_nbr **stack_a, t_algo **algo,
		int size_stack_a)
{
	int		i;

	i = 0;
	if (rotation < size_stack_a / 2)
	{
		while (i < rotation)
		{
			reverse_rotate(stack_a);
			if (!add_algo_link(algo, RRA))
				return (NULL);
			i++;
		}
	}
	else
	{
		while (i < (size_stack_a - rotation))
		{
			rotate(stack_a);
			if (!add_algo_link(algo, RA))
				return (NULL);
			i++;
		}
	}
	return (*algo);
}

int	kick_lower_and_sort(int *biggest_nbrs, int size_stack_a, t_ps **data)
{
	int		not_biggest;

	not_biggest = 0;
	while (not_biggest + 3 < size_stack_a)
	{
		if ((*data)->stack_a->value != biggest_nbrs[0]
			&& (*data)->stack_a->value != biggest_nbrs[1]
			&& (*data)->stack_a->value != biggest_nbrs[2])
		{
			push(&((*data)->stack_b), &((*data)->stack_a));
			if (!add_algo_link(&((*data)->algo), PB))
				return (0);
			not_biggest++;
		}
		else
		{
			rotate(&((*data)->stack_a));
			if (!add_algo_link(&((*data)->algo), RA))
				return (0);
		}
	}
	sort_only_three_nb(&((*data)->stack_a), &((*data)->algo));
	return (1);
}
