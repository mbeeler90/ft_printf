/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_width_precision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/08 10:46:41 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_print_zero(const char **format, t_print *args)
{
	while (args->dot == 1 && args->precision-- > args->digits + args->hash)
		args->arg_len += write(1, "0", 1);
	while (args->width > args->digits + args->sign && args->zero == 1
		&& args->dash == 0 && args->dot == 0)
	{
		args->arg_len += write(1, "0", 1);
		args->width--;
	}
}

static void	ft_print_sign(const char **format, t_print *args)
{
	if (args->neg == 1)
		args->arg_len += write(1, "-", 1);
	else if (args->plus == 1)
		args->arg_len += write(1, "+", 1);
	else if (args->space == 1)
		args->arg_len += write(1, " ", 1);
	else if (args->hash == 1 && **format == 'o')
		args->arg_len += write(1, "0", 1);
	else if (args->hash == 1 && (**format == 'x' || **format == 'p'))
		args->arg_len += write(1, "0x", 2);
	else if (args->hash == 1 && **format == 'X')
		args->arg_len += write(1, "0X", 2);
}

void	ft_print_width_precision(const char **format, t_print *args, t_u64 n)
{
	while (args->width > args->precision + args->sign
		&& args->width > args->digits + args->sign
		&& args->dash == 0 && (args->zero == 0 || args->dot == 1))
	{
		args->arg_len += write(1, " ", 1);
		args->width--;
	}
	if (n == 0 && args->precision2 == 0 && args->dot == 1 && args->width != 0 \
		&& args->dash == 0 && args->hash2 == 0)
		args->arg_len += write(1, " ", 1);
	if ((**format == 'x' || **format == 'X' || **format == 'o') && n != 0 \
		&& args->hash == 1 && args->width != 0 && args->dot == 1 \
		&& args->dash == 0 && args->precision > args->digits \
		&& args->width == args->precision + args->sign)
		args->arg_len += write(1, " ", 1);
	ft_print_sign(format, args);
	ft_print_zero(format, args);
}
