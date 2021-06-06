/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:23:01 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:55:05 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_int(int *nbrs, int size)
{
	int		i;
	int		tmp;

	i = 0;
	while (i + 1 < size)
	{
		if (nbrs[i] > nbrs[i + 1])
		{
			tmp = nbrs[i];
			nbrs[i] = nbrs[i + 1];
			nbrs[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

t_algo	**sort_two_nb_in_b(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	if ((*stack_b)->value > (*stack_b)->next->value)
	{
		if (!add_algo_link(algo, PA) || !add_algo_link(algo, PA))
			return (NULL);
		push(stack_a, stack_b);
		push(stack_a, stack_b);
	}
	else
	{
		if (!add_algo_link(algo, SB) || !add_algo_link(algo, PA)
			|| !add_algo_link(algo, PA))
			return (NULL);
		swap(stack_b);
		push(stack_a, stack_b);
		push(stack_a, stack_b);
	}
	return (algo);
}

int	sort_three_or_two_nb(t_ps **data, int size_stack_a)
{
	if (size_stack_a == 1)
		return (1);
	if (size_stack_a == 3)
	{
		sort_only_three_nb(&((*data)->stack_a), &((*data)->algo));
		return (1);
	}
	else if (size_stack_a == 2)
	{
		if (!sort_two_nb(&((*data)->stack_a), &((*data)->algo)))
			return (0);
		return (1);
	}
	return (0);
}

int	sort_one_or_two_in_b(int size_stack_b, t_ps **data)
{
	if (size_stack_b == 2)
	{
		if (!sort_two_nb_in_b(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo)))
			return (0);
		return (1);
	}
	else if (size_stack_b == 1)
	{
		if (!add_algo_link(&((*data)->algo), PA))
			return (0);
		push(&((*data)->stack_a), &((*data)->stack_b));
		return (1);
	}
	return (0);
}
