/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:37:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:37:09 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_sorting(t_ps **data)
{
	int		size_stack_a;
	int		*biggest_nbrs;

	size_stack_a = size_stack((*data)->stack_a);
	biggest_nbrs = biggest_numbers((*data)->stack_a);
	if (sort_three_or_two_nb(data, size_stack_a))
	{
		free(biggest_nbrs);
		return (1);
	}
	kick_lower_and_sort(biggest_nbrs, size_stack_a, data);
	free(biggest_nbrs);
	return (0);
}

int	create_algo(t_ps **data)
{
	int		size_stack_b;
	int		greater;

	(*data)->end_part = NULL;
	if (init_sorting(data))
		return (1);
	size_stack_b = size_stack((*data)->stack_b);
	while (size_stack_b != 0)
	{
		if (sort_one_or_two_in_b(size_stack_b, data))
			break ;
		greater = send_greater_than_pivot_in_a(&((*data)->end_part),
				data, size_stack_b);
		if (greater == -1)
			return (0);
		send_back_in_a_and_sort(greater, data);
		size_stack_b = size_stack((*data)->stack_b);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps		*data;

	if (argc < 2)
		return (0);
	data = malloc(sizeof(t_ps) * (1));
	if (!data)
		return (1);
	data->stack_a = check_args(argv);
	if (!data->stack_a)
	{
		free_stack(&(data->stack_a));
		free(data);
		ft_putstr("Error\n");
		return (1);
	}
	data->stack_b = NULL;
	data->algo = NULL;
	if (!create_algo(&data))
		return (1);
	print_algo(data->algo);
	free_data(&data);
	return (0);
}
