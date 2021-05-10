/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/10 15:42:41 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
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
*/
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
		if (!count && stack_a->value != biggest_nbrs[0])
		{
			biggest_nbrs[1] = stack_a->value;
			count = 1;
		}
		if (count && biggest_nbrs[1] < stack_a->value && stack_a->value
			!= biggest_nbrs[0])
			biggest_nbrs[1] = stack_a->value;
		stack_a = stack_a->next;	
	}
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count && stack_a->value != biggest_nbrs[0] && stack_a->value != biggest_nbrs[1])
		{
			biggest_nbrs[2] = stack_a->value;
			count = 1;
		}
		if (biggest_nbrs[2] < stack_a->value && stack_a->value
			!= biggest_nbrs[0] && stack_a->value != biggest_nbrs[1])
			biggest_nbrs[2] = stack_a->value;
		stack_a = stack_a->next;
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

t_algo	*sort_three_nb(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	t_nbr		*first;
	t_nbr		*second;
	t_nbr		*third;

	first = (*stack_a);
	second = (*stack_a)->next;
	third = (*stack_a)->next->next;
	if (first->value < second->value && first->value < third->value)
	{
		if (second->value > third->value)
		{
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
		}
	}
	else if (first->value > second->value && first->value > third->value)
	{
		if (second->value < third->value)
		{
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, SB);
			swap(stack_b);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
		}
		else if (second->value > third->value)
		{
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, SB);
			swap(stack_b);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
		}
	}
	else
	{
		if (second->value < third->value)
		{
			add_algo_link(algo, SA);
			swap(stack_a);
		}
		else
		{
			add_algo_link(algo, PB);
			push(stack_b, stack_a);
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
			add_algo_link(algo, SA);
			swap(stack_a);
		}

	}
	return (*algo);
}

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

int		find_pivot(t_nbr *stack)
{
	int		*nbrs;
	int		i;
	int		size;

	size = size_stack(stack);
	if (!(nbrs = malloc(sizeof(int) * size)))
		return (0);
	i = 0;
	while (stack)
	{
		nbrs[i] = stack->value;
		stack = stack->next;
		i++;
	}
	sort_int(nbrs, size);
	return (nbrs[size / 2]);
}

t_algo	*create_algo(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	int		*biggest_nbrs;
	int		size_stack_a;
	int		i;
	int		pivot;

	biggest_nbrs = biggest_numbers(*stack_a);
	size_stack_a = size_stack(*stack_a);
	i = 0;
	while (i < size_stack_a)
	{
//		printf("%d| %d | %d\n", biggest_nbrs[0], biggest_nbrs[1], biggest_nbrs[2]);
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
	sort_three_nb(stack_a, stack_b, algo);
	pivot = find_pivot(*stack_b);
	printf("pivot = %d\n", pivot);
	return (*algo);
}

void	print_algo(t_algo *algo)
{
	int		count_instruction;

	count_instruction = 0;
	while (algo)
	{
		if (algo->instru == 0)
			ft_putstr("sa\n");
		else if (algo->instru == 1)
			ft_putstr("sb\n");
		else if (algo->instru == 2)
			ft_putstr("ss\n");
		else if (algo->instru == 3)
			ft_putstr("pa\n");
		else if (algo->instru == 4)
			ft_putstr("pb\n");
		else if (algo->instru == 5)
			ft_putstr("ra\n");
		else if (algo->instru == 6)
			ft_putstr("rb\n");
		else if (algo->instru == 7)
			ft_putstr("rr\n");
		else if (algo->instru == 8)
			ft_putstr("rra\n");
		else if (algo->instru == 9)
			ft_putstr("rrb\n");
		else if (algo->instru == 10)
			ft_putstr("rrr\n");
		algo = algo->next;
		count_instruction++;
	}
	printf("instruction nb = %d\n", count_instruction);
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
	//print_stacks(stack_a, stack_b);
	create_algo(&stack_a, &stack_b, &algo);
	print_algo(algo);
//	print_stacks(stack_a, stack_b);
	return (0);
}
