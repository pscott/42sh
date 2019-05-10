/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:24 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# define ULL unsigned long long int
# define UL unsigned long int
# define LL long long int
# define L long int
# define BASE_8 "012345678"
# define BASE_16_LOW "0123456789abcdef"
# define BASE_16_UP "0123456789ABCDEF"
# define INIT_LEN 32

/*
** Defining ANSI colors escape codes
*/

# define CONTROL_SIZE 4
# define COLOR_SIZE 5
# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"

/*
** Foreground colors
*/

# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define FG_DFL "\x1b[39m"

/*
** Background colors
*/

# define BG_BLACK "\x1b[40m"
# define BG_RED "\x1b[41m"
# define BG_GREEN "\x1b[42m"
# define BG_YELLOW "\x1b[43m"
# define BG_BLUE "\x1b[44m"
# define BG_MAGENTA "\x1b[45m"
# define BG_CYAN "\x1b[46m"
# define BG_WHITE "\x1b[47m"
# define BG_DFL "\x1b[49m"

# define BOLD_OFF "\x1b[22m"

typedef struct	s_arg
{
	char		type;
	int			width;
	int			width_len;
	int			precision;
	int			precision_len;
	char		fill;
	int			fill_len;
	int			left;
	int			plus;
	int			hash;
	int			l;
	int			dbl;
	int			h;
	int			data_len;
	char		*conv_val;
	char		*string;
	char		*origin;
	int			mall_len;
	int			extra;
}				t_arg;

int				ft_vprintf(const char *format, va_list ap);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_vdprintf(int fd, const char *format, va_list ap);

char			*convert(ULL num, int base, char *rep);
char			*convert_p(L num, int base, char *rep);
int				ft_printf(const char *format, ...);
int				parse_struct(t_arg *specs, va_list arg);
void			ft_itoa_spec(t_arg *specs, LL value);
int				handle_perc(char **fornat, t_arg *specs, va_list arg);
int				print_perc(t_arg *specs, char c);
void			ft_uitoa_spec(t_arg *specs, ULL value);
void			ft_nitoa(t_arg *specs, int n);
void			ft_litoa(t_arg *specs, long int n);
void			ft_llitoa(t_arg *specs, long long int n);
void			ft_uitoa(t_arg *specs, unsigned long long int n);
void			ft_hitoa(t_arg *specs, short int n);
void			ft_hhitoa(t_arg *specs, signed char n);
void			init_specs(t_arg *specs);
void			reset_specs(t_arg *specs);
t_arg			*create_specs(t_arg *specs);
void			malloc_string(t_arg *specs, int len);
void			realloc_if_necessary(t_arg *specs, int len);
int				valid_flags(char **format);
int				is_valid_type(char c);
int				min(int a, int b);
int				max(int a, int b);
void			set_extra(char c, t_arg *specs);
void			init_specs(t_arg *specs);
t_arg			*create_specs(t_arg *specs);
int				ulen(t_arg *specs, ULL value);
int				get_lllen(LL value);
int				get_llen(L value);
int				get_len(int value);
int				get_hlen(short int value);
int				get_hhlen(signed char value);
int				get_ulen(unsigned int value);
int				get_ullen(UL value);
int				get_ulllen(ULL value);
int				get_flags(t_arg *specs, char **format, va_list arg);
int				is_type(char **format, t_arg *specs);
int				is_spec_upper(char c);
void			get_preci(char **format, t_arg *specs);
void			get_extra(char **format, t_arg *specs);
void			format_int(t_arg *specs, LL value);
void			format_unsigned(t_arg *specs, ULL value);
void			format_p(t_arg *specs, L value);
void			format_float(t_arg *specs, va_list arg);
int				unsigned_len(t_arg *spec, ULL value);
void			format_char(t_arg *specs, char c);
void			fill_char(int perc_len, t_arg *specs, char *value);
void			fill_char_left(int perc_len, t_arg *specs, char *value);
void			format_string(t_arg *specs, char *string);
void			format_conv(t_arg *specs, LL value);
int				ft_atoi_move(char **src);
int				null_data(t_arg *specs, ULL value);
int				isprint_special(char c);
void			get_preci_flags(char **format, t_arg *specs);
void			ft_strncat_move(char *src, int n, t_arg *specs);
void			put_ox(t_arg *specs, char *value, int *perc_len, int modif);
void			check_conv_value(t_arg *specs, char *value);
int				ox_len(t_arg *specs);
void			ft_special_memset(t_arg *specs, char c, int len);
void			increm_string(t_arg *specs, int len);
void			increm_format(char **s1, int len);
void			set_data_len(t_arg *specs, LL value);
void			value_d(t_arg *specs, LL value);
void			value_x(t_arg *specs, LL value);
void			value_xx(t_arg *specs, LL value);
void			value_o(t_arg *specs, LL value);
void			value_u(t_arg *specs, ULL value);
void			wildcard(t_arg *specs, va_list arg, int modif);
LL				choose_value(t_arg *specs, LL value);
int				set_i(t_arg *specs);
#endif
