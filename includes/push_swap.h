/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebrun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:17:58 by mlebrun           #+#    #+#             */
/*   Updated: 2021/06/06 11:54:36 by mlebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include "ft.h"

typedef enum e_instruction
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

typedef struct s_nbr
{
	int				value;
	struct s_nbr	*next;
}					t_nbr;

typedef struct s_algo
{
	t_instruction		instru;
	struct s_algo		*next;
}					t_algo;

typedef struct s_ps
{
	t_nbr			*stack_a;
	t_nbr			*stack_b;
	t_algo			*algo;
	t_nbr			*end_part;
}				t_ps;

t_nbr				*check_args(char *argv[]);
void				swap(t_nbr **stack);
void				push(t_nbr **stack_dst, t_nbr **stack_src);
void				rotate(t_nbr **stack);
void				reverse_rotate(t_nbr **stack);
t_nbr				*new_nbr(long long int nb);
void				free_stack(t_nbr **stack);
int					add_algo_link(t_algo **begin_algo, t_instruction instru);
int					*biggest_numbers(t_nbr *stack_a);
void				first_or_second_biggest(t_nbr *stack_a, int *biggest_nbrs,
						t_nbr *first_nb);
void				free_data(t_ps **data);
void				free_algo(t_algo **algo);
void				free_stack(t_nbr **stack);
int					add_nbr_front(t_nbr **nbrs, int nb);
void				delete_first_number(t_nbr **nbrs);
int					less_than_pivot(t_ps **data, int pivot, int size);
int					greater_than_pivot(t_nbr **stack_a, t_nbr **stack_b,
						t_algo **algo, int pivot);
int					find_pivot(t_nbr *stack, int size);
int					print_rotation(t_algo *algo);
void				print_algo(t_algo *algo);
int					send_back_to_b(int *first_less, t_ps **data, t_algo **algo,
						t_nbr **end_part);
int					send_in_b_or_rotate(t_ps **data, int pivot, int *first_less,
						int *greater);
int					send_partition(t_nbr **stack_a, t_nbr **stack_b,
						t_algo **algo, t_nbr **end_partition);
int					send_greater_than_pivot_in_a(t_nbr **end_partition,
						t_ps **data, int size_stack_b);
int					send_back_in_a_and_sort(int greater, t_ps **data);
int					sort_two_nb(t_nbr **stack_a, t_algo **algo);
t_algo				*sort_three_nb_first_lower(t_nbr **stack_a, t_nbr **stack_b,
						t_algo **algo);
t_algo				*sort_three_nb_first_between(t_nbr **stack_a,
						t_nbr **stack_b, t_algo **algo);
t_algo				*sort_three_nb_first_greater(t_nbr **stack_a,
						t_nbr **stack_b, t_algo **algo, int *sorted);
t_algo				*sort_three_nb_first_greater_2(t_nbr **stack_a,
						t_nbr **stack_b, t_algo **algo, int sorted);
t_algo				*sort_three_nb(t_nbr **stack_a, t_nbr **stack_b,
						t_algo **algo);
t_algo				**sort_when_first_greater(t_nbr **stack_a, t_nbr *second,
						t_nbr *third, t_algo **algo);
t_algo				**sort_when_first_less(t_nbr **stack_a,
						t_nbr *second, t_nbr *third, t_algo **algo);
t_algo				**sort_when_first_between(t_nbr **stack_a, t_nbr *second,
						t_nbr *third, t_algo **algo);
t_algo				*sort_only_three_nb(t_nbr **stack_a, t_algo **algo);
void				sort_int(int *nbrs, int size);
t_algo				**sort_two_nb_in_b(t_nbr **stack_a, t_nbr **stack_b,
						t_algo **algo);
int					sort_three_or_two_nb(t_ps **data, int size_stack_a);
int					sort_one_or_two_in_b(int size_stack_b, t_ps **data);
int					size_stack(t_nbr *stack);
t_algo				*rotate_back(int rotation, t_nbr **stack_a, t_algo **algo,
						int size_stack_a);
int					kick_lower_and_sort(int *biggest_nbrs, int size_stack_a,
						t_ps **data);
#endif
