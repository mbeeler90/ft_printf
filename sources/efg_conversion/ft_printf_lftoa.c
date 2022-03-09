/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lftoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/08 10:33:30 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static t_u64	ft_get_number(t_u64 mantissa, t_s16 *offset, t_u64 *num_zero)
{
	t_u64	number;

	if (*offset >= 0)
	{
		if (*offset <= 63)
		{
			number = mantissa;
			number >>= 63 - *offset;
		}
		else
		{
			number = mantissa;
			*num_zero = *offset - 63;
		}
	}
	else
		number = 0;
	return (number);
}

static t_u64	ft_get_fraction(t_u64 mantissa, t_s16 *offset)
{
	t_u64	fraction;

	if (*offset < 63)
	{
		if (*offset < 0)
			fraction = mantissa;
		else
		{
			fraction = mantissa;
			fraction <<= 1 + *offset;
			fraction >>= 1 + *offset;
		}
	}
	else
		fraction = 0;
	return (fraction);
}

static void	ft_get_basics(t_f128 n, t_u64 *num_frac_0s, t_s16 *offset)
{
	t_u64	mantissa;
	t_u64	*doub_ptr;

	doub_ptr = (t_u64 *)(&n);
	mantissa = *doub_ptr;
	doub_ptr += 1;
	*offset = *doub_ptr - 16383;
	num_frac_0s[2] = 0;
	num_frac_0s[0] = ft_get_number(mantissa, offset, &num_frac_0s[2]);
	num_frac_0s[1] = ft_get_fraction(mantissa, offset);
}

static void	ft_add_frac_to_num(char **number, t_print *args, \
			t_u64 *num_frac_0s, t_s16 offset)
{
	char	*fraction;

	if (num_frac_0s[1] == 0)
		ft_strpad_right_inplace(number, '0', args->precision + 1);
	else
	{
		fraction = ft_f_conversion_frac(num_frac_0s[1], offset, args, *number);
		ft_strjoin_inplace(number, &fraction);
	}
}

char	*ft_printf_lftoa(t_f128 n, t_print *args)
{
	t_s16	offset;
	char	*number;
	t_u64	num_frac_0s[3];

	offset = 0;
	ft_get_basics(n, num_frac_0s, &offset);
	if (offset == 16384 && num_frac_0s[0] == 0x8000000000000000)
		return (ft_strdup("inf"));
	else if (offset == 16384)
	{
		args->neg = 0;
		args->plus = 0;
		args->space = 0;
		args->sign = 0;
		return (ft_strdup("nan"));
	}
	if (num_frac_0s[2] == 0)
		number = ft_lutoa(num_frac_0s[0]);
	else
		number = ft_f_conversion_number(num_frac_0s[0], num_frac_0s[2]);
	ft_strpad_right_inplace(&number, '.', 1);
	ft_add_frac_to_num(&number, args, num_frac_0s, offset);
	ft_round_string_inplace(&number);
	return (number);
}
