/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_e_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:40:03 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_get_e(char *result, int *i)
{
	int	e;

	if (!ft_strchr(result, '.'))
		e = ft_strlen(result) - 1;
	else if (*result > '0')
		e = ft_strlen(result) - ft_strlen(ft_strchr(result, '.')) - 1;
	else
	{
		while (*i < (int)ft_strlen(result) && (*(result + *i) < '1'
				|| *(result + *i) > '9'))
			*i += 1;
		if (*i == (int)ft_strlen(result))
		{
			*i = 0;
			e = 0;
		}
		else
			e = (*i - 1) * -1;
	}
	return (e);
}

static void	ft_format_e(char **result, t_print *args)
{
	char	*new_result;

	if (ft_strlen(*result) > 1 && *(*result + 1) != '.')
	{
		if (!ft_strchr(*result, '.'))
			ft_strtrim_char_right_inplace(result, '0');
		else
		{
			new_result = *result;
			*(new_result + 1) = '.';
			*(new_result + 2) = '0';
			*result = ft_strndup(new_result, ft_strlen(new_result) - 1);
			ft_strdel(&new_result);
		}
	}
	if (!ft_strchr(*result, '.') && args->hash == 1)
		ft_strpad_right_inplace(result, '.', 1);
	args->hash = 0;
}

static void	ft_finalize_e(char **result, int e)
{
	char	*new_result;

	new_result = ft_itoa(e);
	if (*new_result != '-')
		ft_strpad_left_inplace(&new_result, '+', 1);
	if (ft_strlen(new_result) == 2)
	{
		ft_strpad_right_inplace(&new_result, '0', 1);
		*(new_result + 2) = *(new_result + 1);
		*(new_result + 1) = '0';
	}
	ft_strjoin_inplace(result, &new_result);
}

static void	ft_change_format_to_e(char **result, t_print *args)
{
	char	*new_result;
	int		i;
	int		e;

	i = 0;
	e = ft_get_e(*result, &i);
	new_result = *result;
	*result = ft_strndup(new_result + i, 1);
	ft_strpad_right_inplace(result, '.', 1);
	while (args->precision2 >= 0)
	{
		i++;
		if (*(new_result + i) != '.')
		{
			ft_strpad_right_inplace(result, *(new_result + i), 1);
			args->precision2--;
		}
	}
	ft_strdel(&new_result);
	ft_round_string_inplace(result);
	ft_format_e(result, args);
	ft_strpad_right_inplace(result, 'e', 1);
	ft_finalize_e(result, e);
}

/*
** print number in e format
*/
void	ft_e_conversion(t_print *args)
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
		ft_change_format_to_e(&result, args);
	ft_print_width(result, args);
	args->arg_len += write(1, result, ft_strlen(result));
	ft_print_hash_dash(args, result);
	ft_strdel(&result);
}
