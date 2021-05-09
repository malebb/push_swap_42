/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/07 11:18:19 by mlebrun          ###   ########.fr       */
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
/*
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
*/
int		*biggest_numbers(t_nbr *stack_a)
{
	int		*biggest_nbrs;
	t_nbr	*first_nb;

	first_nb = stack_a;
	if (!(biggest_nbrs = malloc(sizeof(int) * 3)))
		return (0);
	while (stack_a)
	{
		if (biggest_nbrs[0] < stack_a->value)
			biggest_nbrs[0] = stack_a->value;
		stack_a = stack_a->next;	
	}
	stack_a = first_nb;
	while (stack_a)
	{
		if (biggest_nbrs[1] < stack_a->value && stack_a->value
			!= biggest_nbrs[0])
			biggest_nbrs[1] = stack_a->value;
		stack_a = stack_a->next;	
	}
	stack_a = first_nb;
	while (stack_a)
	{
		if (biggest_nbrs[2] < stack_a->value && stack_a->value
			!= biggest_nbrs[0] && stack_a->value != biggest_nbrs[1])
			biggest_nbrs[2] = stack_a->value;
		stack_a = stack_a->next;	
	}
	return (biggest_nbrs);
}

t_algo	*create_algo(t_nbr **stack_a, t_algo **algo)
{
	int		*biggest_nbrs;

	(void)stack_a;
	biggest_nbrs = biggest_numbers(*stack_a);
	printf("%d | %d | %d\n", biggest_nbrs[0], biggest_nbrs[1], biggest_nbrs[2]);
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
	create_algo(&stack_a, &algo);
	print_algo(algo);
	print_stacks(stack_a, stack_b);
	return (0);
}
