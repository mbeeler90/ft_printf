/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/07 17:22:43 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>//

typedef struct s_print
{
	va_list	ap;
	int		hash;
	int		hash2;
	int		space;
	int		plus;
	int		dash;
	int		zero;
	int		width;
	int		dot;
	int		precision;
	int		precision2;
	int		length;
	int		mod_l;
	int		mod_cap_l;
	int		mod_ll;
	int		mod_h;
	int		mod_hh;
	int		arg_len;
	int		neg;
	int		digits;
	int		sign;
	int		num_uneven;
}	t_print;

int		ft_printf(const char *format, ...);
int		ft_type_conversion(const char **format, t_print *args);
int		ft_set_color(const char **format);
void	ft_initialize_args(t_print *args);
void	ft_cs_conversion(const char **format, t_print *args);
void	ft_diopux_conversion(const char **format, t_print *args);
void	ft_di_conversion(const char **format, t_print *args);
void	ft_oux_conversion(const char **format, t_print *args);
void	ft_p_conversion(const char **format, t_print *args);
t_u64	ft_convert_number(t_print *args, t_s64 num);
int		ft_get_sig_bytes(const char **format, t_print *args, t_u64 n, int div);
void	ft_print_width_precision(const char **format, t_print *args, t_u64 n);
void	ft_print_number(const char **format, t_print *args, t_u64 n, int div);
void	ft_print_dash(t_print *args, t_u64 n);
void	ft_efg_conversion(const char **format, t_print *args);
void	ft_f_conversion(t_print *args);
void	ft_e_conversion(t_print *args);
void	ft_g_conversion(t_print *args);
void	ft_print_g_as_e(char **result, t_print *args, int i, int g);
t_f128	ft_convert_float(t_print *args, t_f128 num);
char	*ft_printf_lftoa(long double n, t_print *args);
char	*ft_f_conversion_number(t_u64 number_dec, t_u64 add_zero_num);
char	*ft_f_conversion_frac(t_u64 frac_dec, t_s16 offset, t_print *args, \
		char *number);
char	*ft_fraction_bintoa(const char *binary, const char *fraction_div, \
		t_print *args);
void	ft_print_width(const char *result, t_print *args);
void	ft_print_hash_dash(t_print *args, char *result);
void	ft_b_conversion(const char **format, t_print *args);

#endif
