/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/08 10:17:34 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_get_g(char *result, int *i)
{
	int	g;

	if (!ft_strchr(result, '.'))
		g = ft_strlen(result) - 1;
	else if (*result > '0')
		g = ft_strlen(result) - ft_strlen(ft_strchr(result, '.')) - 1;
	else
	{
		while (*i < (int)ft_strlen(result) && (*(result + *i) < '1'
				|| *(result + *i) > '9'))
			*i += 1;
		if (*i == (int)ft_strlen(result))
		{
			*i = 0;
			g = 0;
		}
		else
			g = (*i - 1) * -1;
	}
	return (g);
}

static void	ft_print_g_as_f(char **result, t_print *args)
{
	char	*new_result;
	int		i;
	int		g;

	if (ft_strchr(*result, '.'))
	{
		new_result = *result;
		*result = ft_strndup(new_result, args->precision2 + 2);
		ft_round_string_inplace(result);
		ft_strdel(&new_result);
		if (args->hash == 0 && ft_strchr(*result, '.'))
			ft_strtrim_char_right_inplace(result, '0');
		if (args->hash == 0 && *(*result + ft_strlen(*result) - 1) == '.')
			ft_strtrim_char_right_inplace(result, '.');
	}
	if (!ft_strchr(*result, '.') && args->hash == 1)
		ft_strpad_right_inplace(result, '.', 1);
	i = 0;
	g = ft_get_g(*result, &i);
	if (g >= args->precision2 || g < -4)
		ft_print_g_as_e(result, args, i, g);
}

static void	ft_change_format_to_g(char **result, t_print *args)
{
	int		i;
	int		g;

	if (args->precision2 == 0)
		args->precision2 = 1;
	i = 0;
	g = ft_get_g(*result, &i);
	if (g >= args->precision2 || g < -4)
		ft_print_g_as_e(result, args, i, g);
	else
		ft_print_g_as_f(result, args);
	args->hash = 0;
}

void	ft_g_conversion(t_print *args)
{
	t_f128	n;
	char	*result;

	if (args->dot == 0)
	{
		args->precision = 6;
		args->precision2 = 6;
	}
	if (args->mod_cap_l == 1)
		n = ft_convert_float(args, va_arg(args->ap, t_f128));
	else
		n = ft_convert_float(args, (t_f128)va_arg(args->ap, t_f64));
	if (n < 1)
		args->precision = 4951 + args->precision2;
	result = ft_printf_lftoa(n, args);
	if (*result < '0' || *result > '9')
		args->hash = 0;
	else
		ft_change_format_to_g(&result, args);
	ft_print_width(result, args);
	args->arg_len += write(1, result, ft_strlen(result));
	ft_print_hash_dash(args, result);
	ft_strdel(&result);
}
