/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_other_stack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:26:22 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:28:29 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	send_back_to_b(int *first_less, t_ps **data, t_algo **algo,
	t_nbr **end_part)
{
	if (*first_less)
	{
		add_nbr_front(end_part, (*data)->stack_a->value);
		*first_less = 0;
	}
	push(&((*data)->stack_b), &((*data)->stack_a));
	if (!add_algo_link(algo, PB))
		return (0);
	return (1);
}

int	send_in_b_or_rotate(t_ps **data, int pivot, int *first_less,
	int *greater)
{
	int		rotation;

	rotation = 0;
	if ((*data)->stack_a->value < pivot)
	{
		send_back_to_b(first_less, data, &(*data)->algo, &((*data)->end_part));
		*greater = *greater - 1;
	}
	else
	{
		rotate(&(*data)->stack_a);
		if (!add_algo_link(&(*data)->algo, RA))
			return (0);
		rotation = 1;
	}
	return (rotation);
}

int	send_partition(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo, t_nbr **end_partition)
{
	int		count;

	count = 0;
	while ((*stack_b)->value != (*end_partition)->value)
	{
		push(stack_a, stack_b);
		if (!add_algo_link(algo, PA))
			return (-1);
		count++;
	}
	push(stack_a, stack_b);
	if (!add_algo_link(algo, PA))
		return (-1);
	count++;
	delete_first_number(end_partition);
	return (count);
}

int	send_greater_than_pivot_in_a(t_nbr **end_partition, t_ps **data,
	int size_stack_b)
{
	int		greater;
	int		pivot;

	if (*end_partition)
	{
		greater = send_partition(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo), end_partition);
		if (greater == -1)
			return (0);
	}
	else
	{
		pivot = find_pivot((*data)->stack_b, size_stack_b);
		greater = greater_than_pivot(&((*data)->stack_a),
				&((*data)->stack_b), &((*data)->algo), pivot);
	}
	return (greater);
}

int	send_back_in_a_and_sort(int greater, t_ps **data)
{
	int		pivot;

	while (greater > 3)
	{
		pivot = find_pivot((*data)->stack_a, greater);
		greater = less_than_pivot(data, pivot, greater);
	}
	if (greater == 3)
	{
		if (!sort_three_nb(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo)))
			return (0);
	}
	else if (greater == 2)
		sort_two_nb(&((*data)->stack_a), &((*data)->algo));
	return (1);
}
