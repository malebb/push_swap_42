/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/09 11:25:55 by mlebrun          ###   ########.fr       */
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

static t_algo	*new_algo_link(t_instruction instru)
{
	t_algo		*algo_link;

	if (!(algo_link = malloc(sizeof(t_algo) * (1))))
		return (NULL);
	algo_link->instru = instru;
	algo_link->next = NULL;
	return (algo_link);
}


static int		add_algo_link(t_algo **begin_algo, t_instruction instru)
{
	t_algo			*first_algo_link;

	if (!(*begin_algo))
	{
		if (!(*begin_algo = new_algo_link(instru)))
			return (0);
	}
	else
	{
		first_algo_link = *begin_algo;
		while ((*begin_algo)->next != 0)
			*begin_algo = (*begin_algo)->next;
		if (!((*begin_algo)->next = new_algo_link(instru)))
			return (0);
		*begin_algo = first_algo_link;
	}
	return (1);
}

int		*biggest_numbers(t_nbr *stack_a)
{
	int		*biggest_nbrs;
	t_nbr	*first_nb;
	int		count;

	first_nb = stack_a;
	if (!(biggest_nbrs = malloc(sizeof(int) * 3)))
		return (0);
	count = 0;
	while (stack_a)
	{
		if (!count)
			biggest_nbrs[0] = stack_a->value;
		if (biggest_nbrs[0] < stack_a->value)
			biggest_nbrs[0] = stack_a->value;
		stack_a = stack_a->next;
		count = 1;
	}
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count)
			biggest_nbrs[1] = stack_a->value;
		if (biggest_nbrs[1] < stack_a->value && stack_a->value
			!= biggest_nbrs[0])
			biggest_nbrs[1] = stack_a->value;
		stack_a = stack_a->next;	
		count = 1;
	}
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count)
			biggest_nbrs[2] = stack_a->value;
		if (biggest_nbrs[2] < stack_a->value && stack_a->value
			!= biggest_nbrs[0] && stack_a->value != biggest_nbrs[1])
			biggest_nbrs[2] = stack_a->value;
		stack_a = stack_a->next;	
		count = 1;
	}
	return (biggest_nbrs);
}

int		size_stack(t_nbr *stack)
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

t_algo	*create_algo(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	int		*biggest_nbrs;
	int		size_stack_a;
	int		i;

	biggest_nbrs = biggest_numbers(*stack_a);
	size_stack_a = size_stack(*stack_a);
	i = 0;
	while (i < size_stack_a)
	{
		if ((*stack_a)->value != biggest_nbrs[0] && (*stack_a)->value != biggest_nbrs[1] && (*stack_a)->value != biggest_nbrs[2])
		{
			push(stack_b, stack_a);
			add_algo_link(algo, PB);
		}
		else
		{
			rotate(stack_a);
			add_algo_link(algo, RA);
		}
		i++;
	}
	return (*algo);
}

void	print_algo(t_algo *algo)
{
	while (algo)
	{
		printf("Instru = %d\n", algo->instru);
		algo = algo->next;
	}
}

int		main(int argc, char **argv)
{
	t_nbr		*stack_a;
	t_nbr		*stack_b;
	t_algo		*algo;

	(void)argc;
	if (argc < 2)
		return (0);
	if (!(stack_a = check_args(argv)))
	{
		ft_putstr("Error\n");
		return (1);
	}
	stack_b = NULL;
	algo = NULL;
	print_stacks(stack_a, stack_b);
	create_algo(&stack_a, &stack_b, &algo);
	print_algo(algo);
	print_stacks(stack_a, stack_b);
	return (0);
}
