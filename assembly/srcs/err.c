/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:11 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:58:12 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_err(t_file *x, int c)
{
	if (c >= 8 && c <= 13)
		print_err2(x, c);
	else if (c >= 14)
		print_err3(x, c);
	else if (c == 1)
		ft_printf("Champion name too long (Max length 128)\n");
	else if (c == 2)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s",
					x->line_err, x->col_err, "COMMAND_NAME \".name\"\n");
	else if (c == 3)
		ft_printf("Champion comment too long (Max length 2048)\n");
	else if (c == 4)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] %s",
					x->line_err, x->col_err, "COMMAND_COMMENT \".comment\"\n");
	else if (c == 5)
		ft_printf("Lexical error at [%d:%d]\n", x->line_err, x->col_err);
	else if (c == 6)
		ft_printf("%s at token [TOKEN][%03d:%03d] INSTRUCTION \"%s\"\n",
					"Syntax error", x->line_err, x->col_err, x->name_err);
	else if (c == 7)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\"\n",
					x->line_err, x->col_err);
	return (-1);
}

void	print_err2(t_file *x, int c)
{
	if (c == 8)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n",
					x->line_err, x->col_err);
	else if (c == 9)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] REGISTER \"%s\"\n",
					x->line_err, x->col_err, x->name_err);
	else if (c == 10)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] DIRECT \"%s\"\n",
					x->line_err, x->col_err, x->name_err);
	else if (c == 11)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT \"%s\"\n",
					x->line_err, x->col_err, x->name_err);
	else if (c == 12)
	{
		ft_printf("No such label %s while attempting to derefe", x->name_err);
		ft_printf("rence token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
					x->line_err, x->col_err, x->name_err);
	}
	else if (c == 13)
	{
		ft_printf("Invalid instruction at token [TOKEN]");
		ft_printf("[%03d:%03d] INSTRUCTION \"%s\"\n",
					x->line_err, x->col_err, x->name_err);
	}
}

void	print_err3(t_file *x, int c)
{
	if (c == 14)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] END \"(null)\"\n",
					x->line_err, x->col_err);
	else if (c == 15)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] END \"(null)\"\n",
					x->line_err + 1, x->col_err);
	else if (c == 16)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s:\"\n",
					x->line_err, x->col_err, x->name_err);
	else if (c == 17)
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] STRING\n",
					x->line_err, x->col_err);
	else if (c == 20)
		ft_printf("Invalid parameter %d type %s for instruction %s\n",
					x->param_err, x->type_err, x->inst_err);
	else if (c == 21)
		ft_printf("Invalid parameter count for instruction %s\n", x->inst_err);
}
