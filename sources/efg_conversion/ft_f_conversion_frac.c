/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_conversion_frac.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:42:13 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Convert the fraction part of the float
*/
char	*ft_f_conversion_frac(t_u64 frac_dec, t_s16 offset, t_print *args, \
		char *number)
{
	char	*fraction;
	char	*fraction_div;
	char	*fraction_bin;
	int		len;
	int		i;

	if ((number[ft_strlen(number) - 2] - '0') % 2 == 1)
		args->num_uneven = 1;
	fraction_bin = ft_lutobin(frac_dec);
	len = 63 - offset + 1;
	i = ft_strlen(fraction_bin);
	while (fraction_bin[--i] == '0')
		len--;
	ft_strtrim_char_right_inplace(&fraction_bin, '0');
	ft_strtrim_char_left_inplace(&fraction_bin, '0');
	fraction_div = ft_strnew(len);
	ft_memset(fraction_div, '0', len);
	fraction_div[0] = '1';
	fraction = ft_fraction_bintoa(fraction_bin, fraction_div, args);
	ft_strdel(&fraction_bin);
	ft_strdel(&fraction_div);
	return (fraction);
}
