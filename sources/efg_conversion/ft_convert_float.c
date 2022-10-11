/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:36:45 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** convert negative numbers to positive numbers
*/
t_f128	ft_convert_float(t_print *args, t_f128 num)
{
	t_u64	*doub_ptr;

	doub_ptr = (t_u64 *)(&num);
	doub_ptr += 1;
	if ((*doub_ptr << 48) >> 63)
	{
		args->neg = 1;
		num *= -1;
	}
	if (args->neg == 1 || args->space == 1 || args->plus == 1)
		args->sign = 1;
	return (num);
}
