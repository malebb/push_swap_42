/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:18:18 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:20:17 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_two_nb(t_nbr **stack_a, t_algo **algo)
{
	t_nbr		*first;
	t_nbr		*second;

	first = (*stack_a);
	second = (*stack_a)->next;
	if (first->value > second->value)
	{
		if (!add_algo_link(algo, SA))
			return (0);
		swap(stack_a);
	}
	return (1);
}

t_algo	*sort_three_nb_first_lower(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo)
{
	t_nbr		*second;
	t_nbr		*third;

	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (second->value > third->value)
	{
		if (!add_algo_link(algo, PB) || !add_algo_link(algo, SA)
			|| !add_algo_link(algo, PA))
			return (NULL);
		push(stack_b, stack_a);
		swap(stack_a);
		push(stack_a, stack_b);
	}
	return (*algo);
}

t_algo	*sort_three_nb_first_between(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo)
{
	t_nbr		*second;
	t_nbr		*third;

	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (second->value < third->value)
	{
		swap(stack_a);
		if (!add_algo_link(algo, SA))
			return (NULL);
	}
	else
	{
		if (!add_algo_link(algo, PB) || !add_algo_link(algo, SA)
			|| !add_algo_link(algo, PA) || !add_algo_link(algo, SA))
			return (NULL);
		push(stack_b, stack_a);
		swap(stack_a);
		push(stack_a, stack_b);
		swap(stack_a);
	}
	return (*algo);
}

t_algo	*sort_three_nb_first_greater(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo, int *sorted)
{
	t_nbr		*second;
	t_nbr		*third;

	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (second->value < third->value)
	{
		if (!add_algo_link(algo, PB) || !add_algo_link(algo, PB)
			|| !add_algo_link(algo, SB) || !add_algo_link(algo, PA)
			|| !add_algo_link(algo, SA) || !add_algo_link(algo, PA))
			return (NULL);
		push(stack_b, stack_a);
		push(stack_b, stack_a);
		swap(stack_b);
		push(stack_a, stack_b);
		swap(stack_a);
		push(stack_a, stack_b);
	}
	else
		*sorted = 0;
	return (*algo);
}

t_algo	*sort_three_nb_first_greater_2(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo, int sorted)
{
	t_nbr		*second;
	t_nbr		*third;

	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (!sorted && second->value > third->value)
	{
		if (!add_algo_link(algo, PB) || !add_algo_link(algo, SA)
			|| !add_algo_link(algo, PB) || !add_algo_link(algo, SB)
			|| !add_algo_link(algo, PA) || !add_algo_link(algo, SA)
			|| !add_algo_link(algo, PA))
			return (NULL);
		push(stack_b, stack_a);
		swap(stack_a);
		push(stack_b, stack_a);
		swap(stack_b);
		push(stack_a, stack_b);
		swap(stack_a);
		push(stack_a, stack_b);
	}
	return (*algo);
}
