/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_conversion_number.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:42:34 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Convert the number part of the float
*/
char	*ft_f_conversion_number(t_u64 number_dec, t_u64 add_zero_num)
{
	char	*number;
	char	*number_bin;

	number_bin = ft_lutobin(number_dec);
	ft_strtrim_char_left_inplace(&number_bin, '0');
	ft_strpad_right_inplace(&number_bin, '0', add_zero_num);
	number = ft_bintoa(number_bin);
	ft_strdel(&number_bin);
	return (number);
}
