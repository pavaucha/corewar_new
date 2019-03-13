/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:15:14 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 14:27:46 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct				s_header
{
	unsigned int			magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	unsigned int			prog_size;
	char					comment[COMMENT_LENGTH + 1];
}							t_header;

typedef struct				s_file
{
	int						l;
	int						c;
	int						name;
	int						comment;
	int						fd;
	char					*s;
	int						err;
	char					*name_err;
	char					inst_err[5];
	char					type_err[8];
	int						param_err;
	int						col_err;
	int						line_err;
	int						sep;
	int						body;
	int						inst;
	int						param;
	char					**lab;
	struct s_check_label	*label;
	char					**file;
	char					*name_f;
	int						endline;
}							t_file;

typedef struct				s_check_label
{
	int						l;
	int						c;
	char					*name;
	struct s_check_label	*next;
}							t_check_label;

typedef struct				s_ligne
{
	int						pos[3];
	char					*arg;
	char					*label;
	char					instruct[6];
	char					*ligne;
	int						nb_octet_pos;
	int						nb_loctet;
	struct s_ligne			*next;
}							t_ligne;

/*
** check_inst1.c
*/

int							inst_live(char *buf, t_file *x);
int							inst_ld(char *buf, t_file *x);
int							inst_st(char *buf, t_file *x);
int							inst_sub(char *buf, t_file *x);
int							inst_and(char *buf, t_file *x);

/*
** check_inst2.c
*/

int							inst_or(char *buf, t_file *x);
int							inst_xor(char *buf, t_file *x);
int							inst_zjmp(char *buf, t_file *x);
int							inst_ldi(char *buf, t_file *x);
int							inst_sti(char *buf, t_file *x);

/*
** check_inst3.c
*/

int							inst_fork(char *buf, t_file *x);
int							inst_lld(char *buf, t_file *x);
int							inst_lldi(char *buf, t_file *x);
int							inst_lfork(char *buf, t_file *x);
int							inst_aff(char *buf, t_file *x);

/*
** check_label.c
*/

int							fill_exec_label(char *buf, t_file *x,
							int len, int c);
int							fill_label(char *buf, t_file *x, int len, int c);
int							check_label(char *buf, t_file *x);

/*
** check_line.c
*/

int							inst_add(char *buf, t_file *x);
void						check_inst(char *buf, t_file *x, char *inst);
int							body(char *buf, t_file *x);
int							endline(t_file *x, char *buf);
int							check_line(char **buf, t_file *x);

/*
** convert_name_com.c
*/

void						ft_nb_octet(char *str, t_ligne **nline);
void						convert_name_com(char **str, char *name);

/*
** err.c
*/

int							print_err(t_file *x, int c);
void						print_err2(t_file *x, int c);
void						print_err3(t_file *x, int c);

/*
** err2.c
*/

void						fill_err_name(t_file *x, char *buf);
int							save_err(t_file *x, int col, int c);
int							save_err2(t_file *x, char *type, char *inst, int c);
int							endline_err(t_file *x, int col, int c);
int							label_err(t_file *x, t_check_label *lab);

/*
** char_err.c
*/

int							lex_err(char *buf, int i);
int							double_header(t_file *x, char *buf, int i);
void						check_quote(t_file *x, int *save,
							int *quote, int i);
int							char_err(char *buf, t_file *x);

/*
** fill_call_label.c
*/

int							fill_call_label(char *buf, t_file *x, int len);

/*
** find_octet.c
*/

int							ft_arg(t_ligne **line, int fd, int nb, int i);
void						find_octet(t_ligne **begin, int fd, t_header head);

/*
** ft_affiche_header.c
*/

int							ft_swap_bits(char *dst, int sign);
void						ft_affiche_header(t_header head, int fd,
							t_ligne *line, char c);

/*
** ft_encoding.c
*/

int							ft_encoding(t_ligne **line);

/*
** ft_strnew_c.c
*/

int							ft_islabel(char *str);
int							ft_find_label_instruct(int *k, t_ligne **nline,
							char **str);
char						*ft_strnew_c(size_t size, char c);

/*
** header.c
*/

void						check_header2(char *buf, t_file *x);
int							quote_arg(t_file *x, char **buf, char *s2, int *j);
int							before_quote(t_file *x, char *buf, int c);
int							quote(t_file *x, char **buf, int c);
int							header(char **buf, t_file *x, int ret);

/*
** initialize_header.c
*/

t_header					initialize_header(char **str);

/*
** label.c
*/

int							find_size_2(t_ligne **line);
int							find_size(t_ligne **line);
int							ft_is_dir(char *str);
void						ft_label(t_ligne **line, t_ligne *begin, int j);

/*
** main.c
*/

int							usage(t_file *x, char *av);
int							main(int ac, char **av);

/*
** params.c
*/

void						reg(t_file *x, char *buf, char *inst);
int							dir2(t_file *x, char *buf, char *inst, int i);
void						dir(t_file *x, char *buf, char *inst);
void						ind(t_file *x, char *buf, char *inst);

/*
** parse_file.c
*/

char						**fill_file(char **file, int i);
int							check_file(t_file *x, char **buf, int *i, int ret);
int							no_newline(t_file *x, char *buf, int ret);
int							err(t_file *x, int ret, char *buf);
int							parse_file(t_file *x, char *buf);

/*
** swap_bits_16.c
*/

char						*ft_negative_nb(char *str, int i);
int							ft_swap_bits_16(char *dst, int sign);

/*
** tools.c
*/

int							separator(t_file *x);
int							init_var(t_file *x);
void						reset_var(t_file *x, int *i, int ret);
int							no_params(t_file *x, char *buf, int i);
int							fill_file2(t_file *x, int c, char *s2, int j);

/*
** tools2.c
*/

int							free_parsing(t_file *x, int c);
size_t						ft_strlen_custom(const char *s);

/*
** write_instruction.c
*/

void						ft_write_arg(t_ligne **line, int k, int fd);

/*
** wrong_inst.c
*/

int							inst_wrong(t_file *x, char *buf);
int							inst_wrong2(t_file *x, char *buf);

/*
** wrong_params.c
*/

void						other_wrong(t_file *x, char *buf, int c);

#endif
