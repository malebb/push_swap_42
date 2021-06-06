/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:53 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:02:40 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	apply_rotation(t_nbr **stack_a, t_nbr **stack_b,
			char *instruction)
{
	if (!ft_strcmp(instruction, "ra"))
		rotate(stack_a);
	else if (!ft_strcmp(instruction, "rb"))
		rotate(stack_b);
	else if (!ft_strcmp(instruction, "rr"))
	{
		rotate(stack_a);
		rotate(stack_b);
	}
	else if (!ft_strcmp(instruction, "rra"))
		reverse_rotate(stack_a);
	else if (!ft_strcmp(instruction, "rrb"))
		reverse_rotate(stack_b);
	else if (!ft_strcmp(instruction, "rrr"))
	{
		reverse_rotate(stack_a);
		reverse_rotate(stack_b);
	}
	else
		return (0);
	return (1);
}

static int	apply_instruction(t_nbr **stack_a, t_nbr **stack_b,
				char *instruction)
{
	if (!ft_strcmp(instruction, "sa"))
		swap(stack_a);
	else if (!ft_strcmp(instruction, "sb"))
		swap(stack_b);
	else if (!ft_strcmp(instruction, "ss"))
	{
		swap(stack_a);
		swap(stack_b);
	}
	else if (!ft_strcmp(instruction, "pa"))
		push(stack_a, stack_b);
	else if (!ft_strcmp(instruction, "pb"))
		push(stack_b, stack_a);
	else if (!apply_rotation(stack_a, stack_b, instruction))
		return (0);
	return (1);
}

static int	is_sorted(t_nbr *stack)
{
	int		previous_value;
	int		first_nb;

	first_nb = 1;
	while (stack)
	{
		if (!first_nb && (stack->value < previous_value))
			return (0);
		first_nb = 0;
		previous_value = stack->value;
		stack = stack->next;
	}
	return (1);
}
/*
static void	print_stacks(t_nbr *stack_a, t_nbr *stack_b)
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
*/

void	ok_or_ko(t_nbr *stack_a, t_nbr *stack_b)
{
	if (!stack_b && is_sorted(stack_a))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
}

int	main(int argc, char *argv[])
{
	t_nbr		*stack_a;
	t_nbr		*stack_b;
	char		*instruction;

	if (argc < 2)
		return (1);
	stack_a = check_args(argv);
	if (!stack_a)
	{
		ft_putstr("Error\n");
		return (1);
	}
	stack_b = NULL;
	while (gnl(&instruction))
	{
		if (!apply_instruction(&stack_a, &stack_b, instruction))
		{
			ft_putstr("Error\n");
			return (1);
		}
		free(instruction);
	}
	free_stacks_and_instruction(&stack_a, &stack_b, &instruction);
	ok_or_ko(stack_a, stack_b);
	return (0);
}
