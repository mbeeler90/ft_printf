/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/04 10:46:52 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_print_number(const char **format, t_print *args, t_u64 n, int div)
{
	char	digit;

	if (n >= (t_u64)div)
	{
		ft_print_number(format, args, n / div, div);
		ft_print_number(format, args, n % div, div);
	}
	else
	{
		digit = '0' + n;
		if (digit <= '9')
			args->arg_len += write(1, &digit, 1);
		else if (**format == 'X')
		{
			digit += 7;
			args->arg_len += write(1, &digit, 1);
		}
		else
		{
			digit += 39;
			args->arg_len += write(1, &digit, 1);
		}
	}
}
