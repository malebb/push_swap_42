/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:25:08 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:41:23 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_nbr **stack)
{
	t_nbr		*previous;

	previous = NULL;
	while (*stack)
	{
		if (previous)
			free(previous);
		previous = *stack;
		*stack = (*stack)->next;
	}
	if (previous)
		free(previous);
}

void	free_algo(t_algo **algo)
{
	t_algo		*previous;

	previous = NULL;
	while (*algo)
	{
		if (previous)
			free(previous);
		previous = *algo;
		*algo = (*algo)->next;
	}
	if (previous)
		free(previous);
}

void	free_data(t_ps **data)
{
	free_stack(&(*data)->stack_a);
	free_stack(&(*data)->stack_b);
	free_algo(&(*data)->algo);
	free(*data);
}
