/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:56:52 by ephe              #+#    #+#             */
/*   Updated: 2019/09/09 15:58:34 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "op.h"
# include "stdint.h"

# define MODULO			1
# define TWO_BYTES		2
# define READ			4
# define REG			8
# define REG_R			16

# define MY_RED			{191, 33, 47, 255}
# define MY_GREEN		{39, 179, 118, 255}
# define MY_BLUE		{38, 75, 150, 255}
# define MY_YELLOW		{249, 167, 62, 255}
# define MY_GREY		{128, 128, 128, 255}

typedef struct			s_parse_argv
{
	int					i;
	int					count_champ;
	int					is_verbose;
	int					is_dump;
	int					is_nb;
	int					nb_champ;
	int					count_nb;
	int					bool;
	int					is_visu;
}						t_parse_argv;

typedef struct			s_process
{
	int					proc_nb;
	int					exec_cycle;
	int					last_turn_alive;
	int					reg[REG_NUMBER];
	int					opc;
	unsigned int		pc;
	char				carry;
	int					alive;
	int					champ;
	int					error;
}						t_process;

typedef struct			s_champ
{
	int					nb_champ;
	t_header			head;
	char				prog[CHAMP_MAX_SIZE];
	int					count_live;
}						t_champ;

typedef	struct			s_param
{
	int					direct;
	int					indirect;
	int					reg;
	int					val;
}						t_param;

typedef struct			s_field
{
	char				field[MEM_SIZE];
	char				owner[MEM_SIZE];
}						t_field;

typedef struct			s_plist
{
	t_process			proc;
	struct s_plist		*next;
	struct s_plist		*prev;
}						t_plist;

typedef struct			s_op
{
	char				*name;
	int					nb_params;
	int					params[3];
	int					opcode;
	int					cycles;
	char				*description;
	int					carry;
	int					size;
}						t_op;

typedef struct			s_vm
{
	t_field				f;
	t_plist				*process_list;
	t_champ				players[MAX_PLAYERS];
	t_op				op_tab[17];
	int					(*op_fn[17])();
	char				*op_descriptions[17];
	int					nb_players;
	int					last_p_alive;
	int					curr_cycle;
	int					kill_cycle;
	int					kill_check;
	int					nb_lives;
	int					verbose;
	int					cycle_to_die;
	int					curr_alive;
	int					dump_cycle;
	int					dirty;
	int					nb_process;
	int					nb_proc_alive;
	char				print_cycles_to_die;
	int					visu;
}						t_vm;

typedef struct			s_type_argv
{
	char				*str;
	int					(*f)(int argc, char **argv, t_parse_argv *av, t_vm *v);
}						t_type_argv;

typedef struct			s_visu
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Color			color_tab[5];
	SDL_Event			event;
	SDL_Rect			rect;
	SDL_Surface			*surface;
	SDL_Texture			*legend[8];
	SDL_Texture			*player;
	SDL_Texture			*champ_names[4];
	SDL_Texture			*text_tab[5][16];
	TTF_Font			*font;
	int					running;
	int					ttf_on;
	int					sdl_on;
	int					step;
	int					nb_proc_alive;
}						t_visu;

int						ft_number(int argc, char **argv, t_parse_argv *av);
int						wrapper(void *p, char return_error_flag);
int						ft_argv(t_vm *v, int argc, char **argv);
int16_t					reverser_16(int16_t a);
int32_t					reverser_32(int32_t a);
int						read_ind(t_vm *v, int pos, int size);
void					write_ind(char mem[], int pos, int val, int size);
void					write_ind_owner(char mem[], int pos, int val, int size);
int						ft_usage(void);
int						ft_init_champ(int argc, char **argv, t_parse_argv *av,
						t_vm *v);
void					init_op_table(t_vm *v);
int						operate(t_vm *vm);
void					print_op_exec(t_vm *v, t_plist *list,
						t_param *param_tab);
void					exec_catcher(t_vm *v, t_plist *tmp);
void					execute_cycle(t_vm *v, t_plist *tmp, t_visu *sdl);
void					set_unset(t_vm *v, t_plist *tmp);
int						pre_op(t_vm *v, t_process *proc, t_param *params,
						char options);
int						get_offset(int offset);
void					check_error(t_vm *v, t_process *proc,
						t_param *param_tab);
int						op_live(t_vm *v, t_process *proc, t_param *params);
int						op_ld(t_vm *v, t_process *proc, t_param *params);
int						op_st(t_vm *v, t_process *proc, t_param *params);
int						op_add(t_vm *v, t_process *proc, t_param *params);
int						op_sub(t_vm *v, t_process *proc, t_param *params);
int						op_and(t_vm *v, t_process *proc, t_param *params);
int						op_or(t_vm *v, t_process *proc, t_param *params);
int						op_xor(t_vm *v, t_process *proc, t_param *params);
int						op_zjmp(t_vm *v, t_process *proc, t_param *params);
int						op_ldi(t_vm *v, t_process *proc, t_param *params);
int						op_sti(t_vm *v, t_process *proc, t_param *params);
int						op_fork(t_vm *v, t_process *proc, t_param *params,
						t_visu *sdl);
int						op_lld(t_vm *v, t_process *proc, t_param *params);
int						op_lldi(t_vm *v, t_process *proc, t_param *params);
int						op_lfork(t_vm *v, t_process *proc, t_param *params,
						t_visu *sdl);
int						op_aff(t_vm *v, t_process *proc, t_param *params);
void					cycles_to_die(t_vm *v);
void					count_alive(t_vm *v, t_visu *sdl, int reset);
int						load_field(t_vm *v);
int						start_proc_list(t_vm *v);
void					param_setup(t_vm *v, t_process *p, t_param *param_tab);
char					*ft_convert_hexa(unsigned char n);
int						ft_dump(t_vm *v);
void					intro(t_vm *v);
int						verbose(int argc, char **argv, t_parse_argv *av,
						t_vm *v);
int						dump(int argc, char **argv, t_parse_argv *av, t_vm *v);
int						dirty(int argc, char **argv, t_parse_argv *av, t_vm *v);
int						num_champ(int argc, char **argv, t_parse_argv *av,
						t_vm *v);
int						init_visu(int argc, char **argv, t_parse_argv *av,
						t_vm *v);
int						champ(int argc, char **argv, t_parse_argv *av, t_vm *v);
int						open_visu(t_vm *v, t_visu *sdl);
int						update_turn(t_vm *v, t_visu *sdl);
int						render_win(t_vm *v, t_visu *sdl);
int						visu(t_vm *v, t_visu *sdl);
int						init_legend(t_visu *sdl);
int						legend_render(t_visu *sdl);
int						destroy_visu(t_vm *v, t_visu *sdl);
void					free_proc_list(t_vm *v);
int						exit_fail(t_vm *v, t_visu *sdl, t_param *param_tab,
						int free_ist);
int32_t					vm_abs(int n);
int						helper(t_vm *v, t_process p, t_param param, int mod);

#endif
