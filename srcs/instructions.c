/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:38:24 by mlebrun           #+#    #+#             */
/*   Updated: 2021/04/29 10:38:25 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_nbr **stack)
{
	t_nbr		*first_elem;
	t_nbr		*third_elem;

	if (count_nbr(*stack) < 2)
		return ;
	first_elem = *stack;
	*stack = (*stack)->next;
	third_elem = (*stack)->next;
	(*stack)->next = first_elem;
	(*stack)->next->next = third_elem;
}

void	push(t_nbr **stack_dst, t_nbr **stack_src)
{
	t_nbr		*second_nbr;

	if (!(*stack_src))
		return ;
	second_nbr = (*stack_src)->next;
	(*stack_src)->next = *stack_dst;
	*stack_dst = *stack_src;
	*stack_src = second_nbr;
}

void	rotate(t_nbr **stack)
{
	t_nbr	*first_nbr;
	t_nbr	*second_nbr;

	if (!(*stack) || !(*stack)->next)
		return ;
	first_nbr = *stack;
	second_nbr = (*stack)->next;
	while ((*stack)->next != NULL)
		*stack = (*stack)->next;
	(*stack)->next = first_nbr;
	(*stack)->next->next = NULL;
	*stack = second_nbr;
}

void	reverse_rotate(t_nbr **stack)
{
	t_nbr	*first_nbr;
	t_nbr	*last_nbr;

	if (!(*stack) || !(*stack)->next)
		return ;
	first_nbr = *stack;
	while ((*stack)->next->next)
		*stack = (*stack)->next;
	(*stack)->next->next = first_nbr;
	last_nbr = (*stack)->next;
	(*stack)->next = NULL;
	(*stack) = last_nbr;
}
