#include "checker.h" 

long long int	ft_atoi(char *nbr)
{
	long long int	nb;
	int				neg;
	int				i;

	i = 0;
	neg = 1;
	if (nbr[i] == '-')
	{
		i++;
		neg = -1;
	}
	nb = 0;
	while (nbr[i] != '\0')
	{
		nb *= 10;
		nb += nbr[i] - 48;
		i++;
	}
	return (nb * neg);
}

int		only_numbers(char *argv[])
{
	int		i;
	int		j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]) && !(argv[i][j] == '-' && j == 0))
				return (FALSE);
			if (argv[i][j] == '-' && argv[i][j + 1] == '\0')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

t_nbr		*new_nbr(long long int nb)
{
	t_nbr		*nbr;

	if (!(nbr = malloc(sizeof(t_nbr) * (1))))
		return (NULL);
	nbr->value = (int)nb;
	nbr->next = NULL;
	return (nbr);
}

int			add_nbr(t_nbr **nbrs, long long int nb)
{
	t_nbr		*first_nb;	

	if (!(*nbrs))
	{
		if (!(*nbrs = new_nbr(nb)))
			return (0);
	}
	else
	{
		first_nb = *nbrs;
		while ((*nbrs)->next != 0)
			*nbrs = (*nbrs)->next;
		if (!((*nbrs)->next = new_nbr(nb)))
			return (0);
		*nbrs = first_nb;
	}
	return (1);
}

t_nbr		*stock_numbers(char *argv[])
{
	int				i;
	t_nbr			*nbrs;
	long long int	nb;

	i = 1;
	nbrs = NULL;
	while (argv[i] != NULL)
	{
		nb = ft_atoi(argv[i]);
		if (nb < -2147483648 || nb > 2147483647)
			return  (NULL);	
		if (!add_nbr(&nbrs, nb))
			return (NULL);
		i++;
	}
	return (nbrs);
}

int			check_duplicates(t_nbr *nbr)
{
	t_nbr		*first_nbr;
	t_nbr		*nbr_passed;

	first_nbr = nbr;
	nbr_passed = nbr;
	while (nbr)
	{
		while (nbr_passed != nbr)
		{
			if (nbr_passed->value == nbr->value)
				return (0);
			nbr_passed = nbr_passed->next;
		}
		nbr_passed = first_nbr;
		nbr = nbr->next;
	}
	return (1);
}

int			count_nbr(t_nbr *nbrs)
{
	int		count;

	count = 0;
	while (nbrs)
	{
		count++;
		nbrs = nbrs->next;
	}
	return (count);
}

t_nbr		*check_args(char *argv[])
{
	t_nbr		*stack_a;

	if (!only_numbers(argv))
		return (NULL);
	if (!(stack_a = stock_numbers(argv)))
		return (NULL);
	if (!check_duplicates(stack_a))
		return (NULL);
	return (stack_a);
}
/*
int			real_instruction(char *instruction)
{
	if (!ft_strcmp(instruction, "sa") || !ft_strcmp(instruction, "sb")
	 || !ft_strcmp(instruction, "ss") || !ft_strcmp(instruction, "pa")
	 || !ft_strcmp(instruction, "pb") || !ft_strcmp(instruction, "ra")
	 || !ft_strcmp(instruction, "rb") || !ft_strcmp(instruction, "rr")
	 || !ft_strcmp(instruction, "rra") || !ft_strcmp(instruction, "rrb")
	 || !ft_strcmp(instruction, "rrr"))
		return (1);
	return (0);
}
*/

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

int		apply_instruction(t_nbr **stack_a, t_nbr **stack_b, char *instruction)
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
	else if (!ft_strcmp(instruction, "ra"))
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

int		is_sorted(t_nbr *stack)
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

void	print_stacks(t_nbr *stack_a, t_nbr *stack_b)
{
	printf("Stack A\n");
	while (stack_a)
	{
		printf("nb = %d\n", stack_a->value);
		stack_a = stack_a->next;
	}
	printf("Stack B\n");
	while (stack_b)
	{
		printf("nb = %d\n", stack_b->value);
		stack_b = stack_b->next;
	}
}

int		main(int argc, char *argv[])
{
	t_nbr		*stack_a;
	t_nbr		*stack_b;
	char		*instruction;

	if (argc < 2)
		return (1);
	if (!(stack_a = check_args(argv)))
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
	}
	print_stacks(stack_a, stack_b);
	if (!stack_b && is_sorted(stack_a))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	return (0);
}
