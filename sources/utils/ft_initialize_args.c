/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/07 17:23:16 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_initialize_args(t_print *args)
{
	args->hash = 0;
	args->hash2 = 0;
	args->space = 0;
	args->plus = 0;
	args->dash = 0;
	args->zero = 0;
	args->dot = 0;
	args->length = 0;
	args->mod_l = 0;
	args->mod_cap_l = 0;
	args->mod_ll = 0;
	args->mod_h = 0;
	args->mod_hh = 0;
	args->arg_len = 0;
	args->neg = 0;
	args->digits = 0;
	args->sign = 0;
	args->num_uneven = 0;
}
