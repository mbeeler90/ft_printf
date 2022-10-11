/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:33:16 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** print the dash formating
*/
void	ft_print_dash(t_print *args, t_u64 n)
{
	while (args->width > args->precision2 + args->sign - args->hash
		&& args->width > args->digits + args->sign
		&& args->dash == 1)
	{
		args->arg_len += write(1, " ", 1);
		args->width--;
	}
	if (n == 0 && args->precision2 == 0 && args->dot == 1 && args->width != 0 \
		&& args->dash == 1 && args->hash2 == 0)
		args->arg_len += write(1, " ", 1);
}
