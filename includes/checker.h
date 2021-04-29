/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <mlebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:04:19 by mlebrun           #+#    #+#             */
/*   Updated: 2021/04/29 11:04:26 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include "ft.h"
# define TRUE	1
# define FALSE	0

typedef struct		s_nbr
{
	int				value;
	struct s_nbr	*next;
}					t_nbr;

int					gnl(char **line);
t_nbr				*check_args(char *argv[]);
void				swap(t_nbr **stack);
void				push(t_nbr **stack_dst, t_nbr **stack_src);
void				rotate(t_nbr **stack);
void				reverse_rotate(t_nbr **stack);
t_nbr				*stock_numbers(char *argv[]);
int					count_nbr(t_nbr *nbrs);
long long int		ft_atoi(char *nbr);

#endif
