/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/04/30 11:40:26 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		print_stacks(t_nbr *stack_a, t_nbr *stack_b)
{
	printf("A   |   B\n\n");
	while (stack_a || stack_b)
	{
		if (stack_a && stack_b)
		{
			printf("%d   |   %d\n", stack_a->value, stack_b->value);
			stack_a = stack_a->next;
			stack_b = stack_b->next;
		}
		else if (stack_a && !stack_b)
		{
			printf("%d   |   -\n", stack_a->value);
			stack_a = stack_a->next;
		}
		else if (!stack_a && stack_b)
		{
			printf("-   |   %d\n", stack_b->value);
			stack_b = stack_b->next;
		}
	}
}

int		main(int argc, char **argv)
{
	t_nbr		*stack_a;
	t_nbr		*stack_b;

	(void)argc;
	if (argc < 2)
		return (0);
	if (!(stack_a = check_args(argv)))
	{
		ft_putstr("Error\n");
		return (1);
	}
	stack_b = NULL;
	print_stacks(stack_a, stack_b);
	return (0);
}
