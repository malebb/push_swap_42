/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/27 11:34:43 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		less = 0;
int		great = 0;

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
	//printf("instruction nb = %d\n", count_instruction);
}
/*static void		print_stacks(t_nbr *stack_a, t_nbr *stack_b)
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

t_algo	*sort_two_nb(t_nbr **stack_a, t_algo **algo)
{
	t_nbr		*first;
	t_nbr		*second;

	first = (*stack_a);
	second = (*stack_a)->next;
	if (first->value > second->value)
	{
		add_algo_link(algo, SA);
		swap(stack_a);
	}
	return (*algo);
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
			swap(stack_a);
			add_algo_link(algo, SA);
		}
		else
		{
			push(stack_b, stack_a);
			add_algo_link(algo, PB);
			swap(stack_a);
			add_algo_link(algo, SA);
			push(stack_a, stack_b);
			add_algo_link(algo, PA);
			swap(stack_a);
			add_algo_link(algo, SA);
		}

	}
	return (*algo);
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
		if (second->value > third->value)
		{
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, RA);
			rotate(stack_a);
		}
	}
	else if (first->value > second->value && first->value > third->value)
	{
		if (second->value < third->value)
		{
			add_algo_link(algo, RA);
			rotate(stack_a);
		}
		else if (second->value > third->value)
		{
			add_algo_link(algo, SA);
			swap(stack_a);
			add_algo_link(algo, RRA);
			reverse_rotate(stack_a);
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
			add_algo_link(algo, RRA);
			reverse_rotate(stack_a);
		}
	}
		//print_algo(*algo);
//		print_stacks(*stack_a, NULL);
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

int		find_pivot(t_nbr *stack, int size)
{
	int		*nbrs;
	int		i;

	if (!(nbrs = malloc(sizeof(int) * size)))
		return (0);
	i = 0;
	while (stack && i < size)
	{
		nbrs[i] = stack->value;
		stack = stack->next;
		i++;
	}
	sort_int(nbrs, size);
	return (nbrs[size / 2]);
}

int		greater_than_pivot(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo, int pivot)
{
	int		i;
	int		greater;
	int		size;

	i = 0;
	greater = 0;
	size = size_stack(*stack_b);
	while (i < size)
	{
		if ((*stack_b)->value > pivot)
		{
			push(stack_a, stack_b);
			add_algo_link(algo, PA);
			greater++;
			great++;
		}
		else
		{
			rotate(stack_b);
			add_algo_link(algo, RB);
			great++;
		}
		i++;
	}
	return (greater);
}

int		add_nbr_front(t_nbr **nbrs, int nb)
{
	t_nbr	*new_nb;

	if (!(new_nb = new_nbr(nb)))
		return (0);
	new_nb->next = *nbrs;
	*nbrs = new_nb;
	return (1);
}

void	delete_first_number(t_nbr **nbrs)
{
	t_nbr		*next;

	next = (*nbrs)->next;
	free(*nbrs);
	*nbrs = next;
}

int		less_than_pivot(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo, t_nbr **end_part, int pivot, int size)
{
	int		i;
	int		rotation;
	int		greater;
	int		size_stack_a;
	int		first_less;

	i = 0;
	rotation = 0;
	greater = size;
	first_less = 1;
	while (i < size)
	{
		if ((*stack_a)->value < pivot)
		{
			if (first_less)
			{
				add_nbr_front(end_part, (*stack_a)->value);
				first_less = 0;
			}
			push(stack_b, stack_a);
			add_algo_link(algo, PB);
			greater--;
			less++;
		}
		else
		{
			rotate(stack_a);
			add_algo_link(algo, RA);
			rotation++;
			less++;
		}
		i++;
	}
	size_stack_a = size_stack(*stack_a);
	i = 0;
	if (rotation < size_stack_a / 2)
	{
		while (i < rotation)
		{
			reverse_rotate(stack_a);
			add_algo_link(algo, RRA);
			less++;
			i++;
		}
	}
	else
	{
		while (i < (size_stack_a - rotation))
		{
			rotate(stack_a);
			add_algo_link(algo, RA);
			less++;
			i++;
		}
	}
	return (greater);
}

void	print_end_part(t_nbr *end_part)
{
	if (!end_part)
		return ;
	while (end_part)
	{
		//printf("end_part = %d\n", end_part->value);
		end_part = end_part->next;
	}
}

int		send_partition(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo, t_nbr **end_partition)
{
	int		count;

	count = 0;
/*	
	while (*end_partition != NULL)
	{
		printf("nb = %d\n", (*end_partition)->value);
		*end_partition = (*end_partition)->next;
	}
	*/
	//print_stacks(*stack_a, *stack_b);
	while ((*stack_b)->value != (*end_partition)->value)
	{
//		printf("STACK_B = %d %d\n", (*stack_b)->value, (*end_partition)->value);
		push(stack_a, stack_b);
		add_algo_link(algo, PA);
//	printf("hein\n");
		count++;
	}
	push(stack_a, stack_b);
	add_algo_link(algo, PA);
	count++;
	delete_first_number(end_partition);
	return (count);
} 


t_algo	*create_algo(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	int		*biggest_nbrs;
	int		size_stack_a;
	int		size_stack_b;
	int		pivot;
	int		not_biggest;
	int		greater;
	t_nbr	*end_partition;

	end_partition = NULL;
	biggest_nbrs = biggest_numbers(*stack_a);
	size_stack_a = size_stack(*stack_a);
	if (size_stack_a == 3)
	{
		sort_only_three_nb(stack_a, algo);
		return (*algo);
	}
	else if (size_stack_a == 2)
	{
		sort_two_nb(stack_a, algo);
		return (*algo);
	}
	not_biggest = 0;
	while (not_biggest + 3 < size_stack_a)
	{
		if ((*stack_a)->value != biggest_nbrs[0] && (*stack_a)->value != biggest_nbrs[1] && (*stack_a)->value != biggest_nbrs[2])
		{
			push(stack_b, stack_a);
			add_algo_link(algo, PB);
			not_biggest++;
		}
		else
		{
			rotate(stack_a);
			add_algo_link(algo, RA);
		}
	}
	sort_only_three_nb(stack_a, algo);
	size_stack_b = size_stack(*stack_b);
	while (size_stack_b != 0)
	{
		if (size_stack_b == 2)
		{
			if ((*stack_b)->value > (*stack_b)->next->value)
			{
				push(stack_a, stack_b);
				add_algo_link(algo, PA);
				push(stack_a, stack_b);
				add_algo_link(algo, PA);
			}
			else
			{
				swap(stack_b);
				add_algo_link(algo, SB);
				push(stack_a, stack_b);
				add_algo_link(algo, PA);
				push(stack_a, stack_b);
				add_algo_link(algo, PA);
			}
			break ;
		}
		else if (size_stack_b == 1)
		{
			add_algo_link(algo, PA);
			push(stack_a, stack_b);
			break ;
		}
		if (end_partition)
			greater = send_partition(stack_a, stack_b, algo, &end_partition);
		else
		{
			pivot = find_pivot(*stack_b, size_stack_b);
			greater = greater_than_pivot(stack_a, stack_b, algo, pivot);
		}
		while (greater > 3)
		{
			pivot = find_pivot(*stack_a, greater);
			greater = less_than_pivot(stack_a, stack_b, algo, &end_partition, pivot, greater);
		}
		if (greater == 3)
			sort_three_nb(stack_a, stack_b, algo);
		else if (greater == 2)
			sort_two_nb(stack_a, algo);
		print_end_part(end_partition);
		size_stack_b = size_stack(*stack_b);
	}
	return (*algo);
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
	create_algo(&stack_a, &stack_b, &algo);
	print_algo(algo);
//	print_stacks(stack_a, stack_b);
	//printf("less = %d | greater = %d\n", less, great);
	return (0);
}
