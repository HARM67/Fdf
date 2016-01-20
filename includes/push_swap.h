/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 07:25:39 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 07:27:02 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"
# define ABS(x) ((x > 0) ? x : -x)
# define MAX_BLOCK 0.3
# define ANALYZE 10
# define RA 1
# define RB 2
# define RR 3
# define RRA 4
# define RRB 5
# define RRR 6
# define SA 7
# define SB 8
# define SS 9
# define PA 10
# define PB 11

typedef struct s_comm	t_comm;
typedef struct s_elem	t_elem;
typedef struct s_stack	t_stack;
typedef struct s_app	t_app;

struct					s_elem
{
	long int			nbr;
	long int			pre_nbr;
	t_elem				*next;
	t_elem				*previous;
	t_elem				*pre_next;
	t_elem				*pre_previous;
	char				change;
	unsigned int		read_nbr;
	unsigned int		dec;
	int					gain;
	char				what_stack;
	unsigned int		current_nbr;
	unsigned int		generation;
	unsigned int		zone_size;
	unsigned int		need_swap;
	unsigned int		move_b;
	int					distance_a;
	int					distance_b;
	unsigned int		cost;
};

struct					s_stack
{
	t_elem				*first;
	t_elem				*second;
	t_elem				*last;
	unsigned int		size;
	unsigned int		stack_nbr;
};

struct					s_comm
{
	unsigned char		command;
	t_comm				*previous;
	t_comm				*next;
};

struct					s_app
{
	unsigned int		ac;
	char				**av;
	unsigned int		nbr_nb;
	t_stack				a;
	t_stack				b;
	t_elem				*pre;
	t_elem				*pre_last;
	t_elem				*zone_select;
	t_comm				*resolution;
	t_comm				*last_resol;
	t_comm				*cursor;
	char				out;
	int					tmp;
	char				color;
	char				debug;
	char				manual;
	char				manual_debug;
	char				file;
	char				highlight;
	char				result;
	int					temoin;
	unsigned int		gene_nb;
	unsigned int		best;
	unsigned int		nbr_to_b;
	int					b_dest;
	unsigned int		nb_cmd;
	unsigned int		nb_cmd2;
	unsigned int		nb_cmd_tab[12];
	t_elem				*low_cost;
	unsigned int		next_cmd;
};

void					init_app(t_app **app, int ac, char **av);
void					run_app(t_app *app);

void					put_error(void);

void					init_stack(t_app *app);

void					read_arg(t_app *app);
void					print_stack(t_stack *stack, t_app *app);
void					print_stacks(t_app *app);
void					conform_stack(t_stack *stack);

void					swap(t_stack *stack);
void					push(t_stack *dest, t_stack *src);
void					rotate(t_stack *stack);
void					reverse_rotate(t_stack *stack);

int						manual_reverse_rotate(t_app *app, char *tmp);
int						manual_rotate(t_app *app, char *tmp);
int						manual_push(t_app *app, char *tmp);
int						manual_swap(t_app *app, char *tmp);
void					manual(t_app *app);

void					pre_resolve(t_app *app);

int						control(t_app *app);

t_elem					*new_elem(long int data, t_elem *previous);
void					control_double(t_stack *stack);

void					from_file(t_app *app);

long int				ft_atoi_8(const char *str);

int						ft_strtest(char *str, int (*f)(int));
int						control_arg(char *str);

void					read_elem(t_app *app, int i, unsigned int nbr_nb);

void					manual_debug(t_app *app);
void					set_stack_numbers(t_app *app);

/*
** zone.c
*/
void					zones_size(t_app *app);
void					select_zone(t_app *app);

/*
** calc_stat.c
*/
void					calc_stat(t_app *app);

/*
** print_stack.c
*/
void					print_stacks_details(t_app *app);

/*
** need_push.c
*/
int						need_swap(t_app *app);

/*
** nav.c
*/
t_elem					*next(t_app *app, t_elem *elem);
t_elem					*previous(t_app *app, t_elem *elem);
t_elem					*pre_previous(t_app *app, t_elem *elem);
t_elem					*pre_next(t_app *app, t_elem *elem);

/*
** make_cost.c
*/
void					make_costs(t_app *app);

/*
** go.c
*/
void					go(t_app *app, t_elem *elem);

/*
** come_to_start.c
*/
void					come_to_start(t_app *app);

void					go_b(t_app *app);

void					resolution(t_app *app);

/*
** for_resolution
*/
void					make_dec(t_app *app);
void					count_to_b(t_app *app);
void					last_swap(t_app *app);
void					recup_dans_b(t_app *app);

/*
** resolution.c
*/
void					resolution(t_app *app);

/*
** command.c
*/
void					insert_command(t_app *app, unsigned char command);
void					print_commands(t_app *app);

/*
** do_command.c
*/
void					do_command(t_app *app, unsigned char command);
void					do_reverse_command(t_app *app, unsigned char command);
#endif
