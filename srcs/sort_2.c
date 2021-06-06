/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:20:25 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:22:51 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_algo	*sort_three_nb(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	t_nbr		*second;
	t_nbr		*third;
	int			sorted;

	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if ((*stack_a)->value < second->value && (*stack_a)->value < third->value)
	{
		if (!sort_three_nb_first_lower(stack_a, stack_b, algo))
			return (NULL);
	}
	else if ((*stack_a)->value > second->value
		&& (*stack_a)->value > third->value)
	{
		sorted = 1;
		if (!sort_three_nb_first_greater(stack_a, stack_b, algo, &sorted)
			|| !sort_three_nb_first_greater_2(stack_a, stack_b, algo, sorted))
			return (NULL);
	}
	else
	{
		if (!sort_three_nb_first_between(stack_a, stack_b, algo))
			return (NULL);
	}
	return (*algo);
}

t_algo	**sort_when_first_greater(t_nbr **stack_a, t_nbr *second,
		t_nbr *third, t_algo **algo)
{
	if (second->value < third->value)
	{
		if (!add_algo_link(algo, RA))
			return (NULL);
		rotate(stack_a);
	}
	else if (second->value > third->value)
	{
		if (!add_algo_link(algo, SA) || !add_algo_link(algo, RRA))
			return (NULL);
		swap(stack_a);
		reverse_rotate(stack_a);
	}
	return (algo);
}

t_algo	**sort_when_first_less(t_nbr **stack_a,
		t_nbr *second, t_nbr *third, t_algo **algo)
{
	if (second->value > third->value)
	{
		if (!add_algo_link(algo, SA) || !add_algo_link(algo, RA))
			return (NULL);
		swap(stack_a);
		rotate(stack_a);
	}
	return (algo);
}

t_algo	**sort_when_first_between(t_nbr **stack_a, t_nbr *second,
		t_nbr *third, t_algo **algo)
{
	if (second->value < third->value)
	{
		if (!add_algo_link(algo, SA))
			return (NULL);
		swap(stack_a);
	}
	else
	{
		if (!add_algo_link(algo, RRA))
			return (NULL);
		reverse_rotate(stack_a);
	}
	return (algo);
}

t_algo	*sort_only_three_nb(t_nbr **stack_a, t_algo **algo)
{
	t_nbr		*first;
	t_nbr		*second;
	t_nbr		*third;

	first = (*stack_a);
	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (first->value < second->value && first->value < third->value)
	{
		sort_when_first_less(stack_a, second, third, algo);
	}
	else if (first->value > second->value && first->value > third->value)
	{
		sort_when_first_greater(stack_a, second, third, algo);
	}
	else
	{
		sort_when_first_between(stack_a, second, third, algo);
	}
	return (*algo);
}
