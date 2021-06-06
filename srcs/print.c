/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:15:49 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:16:22 by mlebrun          ###   ########.fr       */
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
