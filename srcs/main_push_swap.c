/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/04 11:37:51 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	print_rotation(t_algo *algo)
{
	int		found;

	found = 1;
	if (algo->instru == 5)
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
	else
		found = 0;
	return (found);
}

void	print_algo(t_algo *algo)
{
	int		count_instruction;
	int		is_rotation;

	count_instruction = 0;
	while (algo)
	{
		is_rotation = print_rotation(algo);
		if (!is_rotation)
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
		}
		algo = algo->next;
		count_instruction++;
	}
}

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

	algo_link = malloc(sizeof(t_algo) * (1));
	if (!algo_link)
		return (NULL);
	algo_link->instru = instru;
	algo_link->next = NULL;
	return (algo_link);
}

static int	add_algo_link(t_algo **begin_algo, t_instruction instru)
{
	t_algo			*first_algo_link;

	if (!(*begin_algo))
	{
		*begin_algo = new_algo_link(instru);
		if (!(*begin_algo))
			return (0);
	}
	else
	{
		first_algo_link = *begin_algo;
		while ((*begin_algo)->next != 0)
			*begin_algo = (*begin_algo)->next;
		(*begin_algo)->next = new_algo_link(instru);
		if (!(*begin_algo)->next)
			return (0);
		*begin_algo = first_algo_link;
	}
	return (1);
}

void	first_or_second_biggest(t_nbr *stack_a, int *biggest_nbrs,
		t_nbr *first_nb)
{
	int		count;

	count = 0;
	while (stack_a)
	{
		if (!count || biggest_nbrs[0] < stack_a->value)
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
}

int	*biggest_numbers(t_nbr *stack_a)
{
	int		*biggest_nbrs;
	t_nbr	*first_nb;
	int		count;

	first_nb = stack_a;
	biggest_nbrs = malloc(sizeof(int) * 3);
	if (!biggest_nbrs)
		return (0);
	first_or_second_biggest(stack_a, biggest_nbrs, first_nb);
	stack_a = first_nb;
	count = 0;
	while (stack_a)
	{
		if (!count && stack_a->value != biggest_nbrs[0]
			&& stack_a->value != biggest_nbrs[1])
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

int	size_stack(t_nbr *stack)
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

int		sort_two_nb(t_nbr **stack_a, t_algo **algo)
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

int	find_pivot(t_nbr *stack, int size)
{
	int		*nbrs;
	int		i;

	nbrs = malloc(sizeof(int) * size);
	if (!nbrs)
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

int	greater_than_pivot(t_nbr **stack_a, t_nbr **stack_b,
	t_algo **algo, int pivot)
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
			if (!add_algo_link(algo, PA))
				return (-1);
			greater++;
		}
		else
		{
			rotate(stack_b);
			if (!add_algo_link(algo, RB))
				return (-1);
		}
		i++;
	}
	return (greater);
}

int	add_nbr_front(t_nbr **nbrs, int nb)
{
	t_nbr	*new_nb;

	new_nb = new_nbr(nb);
	if (!new_nb)
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

t_algo	*rotate_back(int rotation, t_nbr **stack_a, t_algo **algo,
		int size_stack_a)
{
	int		i;

	i = 0;
	if (rotation < size_stack_a / 2)
	{
		while (i < rotation)
		{
			reverse_rotate(stack_a);
			if (!add_algo_link(algo, RRA))
				return (NULL);
			i++;
		}
	}
	else
	{
		while (i < (size_stack_a - rotation))
		{
			rotate(stack_a);
			if (!add_algo_link(algo, RA))
				return (NULL);
			i++;
		}
	}
	return (*algo);
}

int	send_back_to_b(int *first_less, t_ps **data, t_algo **algo,
	t_nbr **end_part)
{
	if (*first_less)
	{
		add_nbr_front(end_part, (*data)->stack_a->value);
		*first_less = 0;
	}
	push(&((*data)->stack_b), &((*data)->stack_a));
	if (!add_algo_link(algo, PB))
		return (0);
	return (1);
}

int	send_in_b_or_rotate(t_ps **data, int pivot, int *first_less,
	int *greater)
{
	int		rotation;

	rotation = 0;
	if ((*data)->stack_a->value < pivot)
	{
		send_back_to_b(first_less, data, &(*data)->algo, &((*data)->end_part));
		*greater = *greater - 1;
	}
	else
	{
		rotate(&(*data)->stack_a);
		if (!add_algo_link(&(*data)->algo, RA))
			return (0);
		rotation = 1;
	}
	return (rotation);
}

int	less_than_pivot(t_ps **data, int pivot, int size)
{
	int		i;
	int		rotation;
	int		greater;
	int		first_less;
	int		size_stack_a;

	i = 0;
	rotation = 0;
	greater = size;
	first_less = 1;
	while (i < size)
	{
		rotation += send_in_b_or_rotate(data, pivot, &first_less, &greater);
		i++;
	}
	size_stack_a = size_stack((*data)->stack_a);
	rotate_back(rotation, &(*data)->stack_a, &(*data)->algo, size_stack_a);
	return (greater);
}

int	send_partition(t_nbr **stack_a, t_nbr **stack_b,
		t_algo **algo, t_nbr **end_partition)
{
	int		count;

	count = 0;
	while ((*stack_b)->value != (*end_partition)->value)
	{
		push(stack_a, stack_b);
		if (!add_algo_link(algo, PA))
			return (-1);
		count++;
	}
	push(stack_a, stack_b);
	if (!add_algo_link(algo, PA))
		return (-1);
	count++;
	delete_first_number(end_partition);
	return (count);
}

t_algo	**sort_two_nb_in_b(t_nbr **stack_a, t_nbr **stack_b, t_algo **algo)
{
	if ((*stack_b)->value > (*stack_b)->next->value)
	{
		if (!add_algo_link(algo, PA) || !add_algo_link(algo, PA))
			return (NULL);
		push(stack_a, stack_b);
		push(stack_a, stack_b);
	}
	else
	{
		if (!add_algo_link(algo, SB) || !add_algo_link(algo, PA)
			|| !add_algo_link(algo, PA))
			return (NULL);
		swap(stack_b);
		push(stack_a, stack_b);
		push(stack_a, stack_b);
	}
	return (algo);
}

int	sort_three_or_two_nb(t_ps **data, int size_stack_a)
{
	if (size_stack_a == 3)
	{
		sort_only_three_nb(&((*data)->stack_a), &((*data)->algo));
		return (1);
	}
	else if (size_stack_a == 2)
	{
		if (!sort_two_nb(&((*data)->stack_a), &((*data)->algo)))
			return (0);
		return (1);
	}
	return (0);
}

int	kick_lower_and_sort(int *biggest_nbrs, int size_stack_a, t_ps **data)
{
	int		not_biggest;

	not_biggest = 0;
	while (not_biggest + 3 < size_stack_a)
	{
		if ((*data)->stack_a->value != biggest_nbrs[0]
			&& (*data)->stack_a->value != biggest_nbrs[1]
			&& (*data)->stack_a->value != biggest_nbrs[2])
		{
			push(&((*data)->stack_b), &((*data)->stack_a));
			if (!add_algo_link(&((*data)->algo), PB))
				return (0);
			not_biggest++;
		}
		else
		{
			rotate(&((*data)->stack_a));
			if (!add_algo_link(&((*data)->algo), RA))
				return (0);
		}
	}
	sort_only_three_nb(&((*data)->stack_a), &((*data)->algo));
	return (1);
}

int	sort_one_or_two_in_b(int size_stack_b, t_ps **data)
{
	if (size_stack_b == 2)
	{
		if (!sort_two_nb_in_b(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo)))
			return (0);
		return (1);
	}
	else if (size_stack_b == 1)
	{
		if (!add_algo_link(&((*data)->algo), PA))
			return (0);
		push(&((*data)->stack_a), &((*data)->stack_b));
		return (1);
	}
	return (0);
}

int	send_greater_than_pivot_in_a(t_nbr **end_partition, t_ps **data,
	int size_stack_b)
{
	int		greater;
	int		pivot;

	if (*end_partition)
	{
		greater = send_partition(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo), end_partition);
		if (greater == -1)
			return (0);
	}
	else
	{
		pivot = find_pivot((*data)->stack_b, size_stack_b);
		greater = greater_than_pivot(&((*data)->stack_a),
				&((*data)->stack_b), &((*data)->algo), pivot);
	}
	return (greater);
}

int	send_back_in_a_and_sort(int greater, t_ps **data)
{
	int		pivot;

	while (greater > 3)
	{
		pivot = find_pivot((*data)->stack_a, greater);
		greater = less_than_pivot(data, pivot, greater);
	}
	if (greater == 3)
	{
		if (!sort_three_nb(&((*data)->stack_a), &((*data)->stack_b),
				&((*data)->algo)))
			return (0);
	}
	else if (greater == 2)
		sort_two_nb(&((*data)->stack_a), &((*data)->algo));
	return (1);
}

t_algo	*create_algo(t_ps **data)
{
	int		*biggest_nbrs;
	int		size_stack_b;
	int		size_stack_a;
	int		greater;

	(*data)->end_part = NULL;
	biggest_nbrs = biggest_numbers((*data)->stack_a);
	size_stack_a = size_stack((*data)->stack_a);
	if (sort_three_or_two_nb(data, size_stack_a))
		return ((*data)->algo);
	kick_lower_and_sort(biggest_nbrs, size_stack_a, data);
	size_stack_b = size_stack((*data)->stack_b);
	while (size_stack_b != 0)
	{
		if (sort_one_or_two_in_b(size_stack_b, data))
			break ;
		greater = send_greater_than_pivot_in_a(&((*data)->end_part),
				data, size_stack_b);
		if (greater == -1)
			return (NULL);
		send_back_in_a_and_sort(greater, data);
		size_stack_b = size_stack((*data)->stack_b);
	}
	return ((*data)->algo);
}

int	main(int argc, char **argv)
{
	t_ps		*data;

	if (argc < 2)
		return (0);
	data = malloc(sizeof(t_ps) * (1));
	if (!data)
		return (0);
	data->stack_a = check_args(argv);
	if (!data->stack_a)
	{
		ft_putstr("Error\n");
		return (1);
	}
	data->stack_b = NULL;
	data->algo = NULL;
	if (!create_algo(&data))
		return (1);
	print_algo(data->algo);
//	free_data(&data);
	return (0);
}
