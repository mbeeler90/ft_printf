/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_sig_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:29:20 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** function to determine how many significant bytes have to be printed based
** on the selected format
*/
int	ft_get_sig_bytes(const char **format, t_print *args, t_u64 n, int div)
{
	int	digits;

	digits = 1;
	if (args->neg == 1 || args->space == 1 || args->plus == 1
		|| args->hash == 1)
		args->sign = 1;
	if (args->hash == 1
		&& (**format == 'x' || **format == 'X' || **format == 'p'))
	{
		args->sign = 2;
		args->precision += 1;
		args->precision2 += 1;
	}
	while (n / div > 0)
	{
		n /= div;
		digits++;
	}
	return (digits);
}
