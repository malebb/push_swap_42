/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 10:54:38 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:56:36 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_stacks_and_instruction(t_nbr **stack_a, t_nbr **stack_b,
		char **instruction)
{
	free_stack(stack_a);
	free_stack(stack_b);
	free(*instruction);
}
