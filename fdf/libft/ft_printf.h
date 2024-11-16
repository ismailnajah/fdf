/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:08:01 by inajah            #+#    #+#             */
/*   Updated: 2024/11/16 10:33:52 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

typedef enum e_flag
{
	INVALID_FLAG,
	DOT,
	ZERO,
	HASH,
	SPACE,
	PLUS,
	DASH,
	FLAG_COUNT,
}	t_flag;

typedef enum e_specifier
{
	INVALID_SPECIFIER,
	CHAR,
	STRING,
	ADDRESS,
	SIGNED_DECIMAL,
	UNSIGNED_DECIMAL,
	LOWER_HEX,
	UPPER_HEX,
	PERCENT_SIGN,
}	t_specifier;

typedef struct s_format
{
	t_flag		*flags;
	int			width;
	int			precision;
	char		padding_char;
	t_specifier	specifier;
}	t_format;

t_format	*ft_fmt_init(void);
void		ft_fmt_clear(t_format **fmt);
void		ft_fmt_reset(t_format *fmt);

int			ft_parse_format(const char *fmt_str, size_t start, t_format *fmt);

int			ft_print_char_spec(char c, t_format *fmt);
int			ft_print_str_spec(char *str, t_format *fmt);
int			ft_print_addr_spec(void *addr, t_format *fmt);
int			ft_print_dec_spec(int d, t_format *fmt);
int			ft_print_udec_spec(unsigned int d, t_format *fmt);
int			ft_print_hex_spec(unsigned int x, int upper, t_format *fmt);
int			ft_print_percent_spec(t_format *format);
int			ft_print_decimal_to_base(unsigned long nb, char *base_symb);
int			ft_print_zero_value(t_format *fmt);
int			ft_count_digits_base(unsigned long nb, size_t base);

int			ft_skip_digits(const char *fmt, size_t i);
int			ft_padd_output(t_format *fmt, int str_size);
int			ft_padd_nb_zeros(unsigned int nb, int precision, int base);
long long	ft_abs(long long nb);
char		ft_get_sign(long long d);

int			ft_printf(const char *str, ...);
#endif
