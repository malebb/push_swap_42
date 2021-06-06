/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:33:52 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:35:09 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
