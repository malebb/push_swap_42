/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:17:58 by mlebrun           #+#    #+#             */
/*   Updated: 2021/05/04 10:28:07 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include "ft.h"

typedef enum	e_instruction
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}				t_instruction;

typedef struct		s_nbr
{
	int				value;
	struct s_nbr	*next;
}					t_nbr;

typedef struct		s_algo
{
	t_instruction		instru;
	struct s_algo		*next;
}					t_algo;

t_nbr				*check_args(char *argv[]);
#endif
