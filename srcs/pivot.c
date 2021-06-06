/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:28:56 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:31:46 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_pivot(t_nbr *stack, int size)
{
	int		*nbrs;
	int		i;
	int		pivot;

	nbrs = malloc(sizeof(int) * size);
	if (!nbrs)
		return (0);
	i = 0;
	while (stack && i < size)
	{
		nbrs[i] = stack->value;
		stack = stack->next;
		i++;
	}
	sort_int(nbrs, size);
	pivot = nbrs[size / 2];
	free(nbrs);
	return (pivot);
}

int	greater_than_pivot(t_nbr **stack_a, t_nbr **stack_b,
	t_algo **algo, int pivot)
{
	int		i;
	int		greater;
	int		size;

	i = 0;
	greater = 0;
	size = size_stack(*stack_b);
	while (i < size)
	{
		if ((*stack_b)->value > pivot)
		{
			push(stack_a, stack_b);
			if (!add_algo_link(algo, PA))
				return (-1);
			greater++;
		}
		else
		{
			rotate(stack_b);
			if (!add_algo_link(algo, RB))
				return (-1);
		}
		i++;
	}
	return (greater);
}

int	less_than_pivot(t_ps **data, int pivot, int size)
{
	int		i;
	int		rotation;
	int		greater;
	int		first_less;
	int		size_stack_a;

	i = 0;
	rotation = 0;
	greater = size;
	first_less = 1;
	while (i < size)
	{
		rotation += send_in_b_or_rotate(data, pivot, &first_less, &greater);
		i++;
	}
	size_stack_a = size_stack((*data)->stack_a);
	rotate_back(rotation, &(*data)->stack_a, &(*data)->algo, size_stack_a);
	return (greater);
}
