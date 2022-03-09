/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/04 14:45:26 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_print_width(const char *result, t_print *args)
{
	int	len;

	len = ft_strlen(result);
	while (args->width > len + args->sign + args->hash
		&& args->dash == 0 && args->zero == 0)
	{
		args->arg_len += write(1, " ", 1);
		args->width--;
	}
	if (args->neg == 1)
		args->arg_len += write(1, "-", 1);
	else if (args->plus == 1)
		args->arg_len += write(1, "+", 1);
	else if (args->space == 1)
		args->arg_len += write(1, " ", 1);
	while (args->width > len + args->sign + args->hash
		&& args->zero == 1
		&& args->dash == 0)
	{
		args->arg_len += write(1, "0", 1);
		args->width--;
	}
}
