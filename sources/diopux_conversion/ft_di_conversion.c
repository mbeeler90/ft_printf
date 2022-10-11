/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:27:45 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** print numbers and in the right formating
*/
void	ft_di_conversion(const char **format, t_print *args)
{
	t_u64	n;

	args->hash = 0;
	if (args->mod_l == 1 || args->mod_ll == 1)
		n = ft_convert_number(args, va_arg(args->ap, t_s64));
	else if (args->mod_h == 1)
		n = ft_convert_number(args, (t_s64)(t_s16)va_arg(args->ap, t_s32));
	else if (args->mod_hh == 1)
		n = ft_convert_number(args, (t_s64)(t_s8)va_arg(args->ap, t_s32));
	else
		n = ft_convert_number(args, (t_s64)va_arg(args->ap, t_s32));
	args->digits = ft_get_sig_bytes(format, args, n, 10);
	ft_print_width_precision(format, args, n);
	if (n != 0 || args->precision2 != 0 || args->dot == 0)
		ft_print_number(format, args, n, 10);
	ft_print_dash(args, n);
}
