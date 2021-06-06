/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:17:04 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:40:19 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	add_algo_link(t_algo **begin_algo, t_instruction instru)
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
