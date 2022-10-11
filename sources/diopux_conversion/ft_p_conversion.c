/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:32:48 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** print the address in the right formating
*/
void	ft_p_conversion(const char **format, t_print *args)
{
	t_u64	n;

	args->plus = 0;
	args->space = 0;
	args->zero = 0;
	args->hash = 1;
	n = (t_u64)va_arg(args->ap, void *);
	args->digits = ft_get_sig_bytes(format, args, n, 16);
	if (n == 0 && args->dot == 1 && args->width != 0)
		args->width++;
	else if (n == 0 && args->dot == 1)
		args->precision++;
	ft_print_width_precision(format, args, n);
	if (n != 0 || args->dot == 0)
		ft_print_number(format, args, n, 16);
	ft_print_dash(args, n);
}
