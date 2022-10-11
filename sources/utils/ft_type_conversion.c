/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 16:23:44 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Check the modifiers for the current conversion.
*/
static void	ft_check_modifier(const char **format, t_print *args)
{
	if (**format == 'l')
		args->mod_l = 1;
	else if (**format == 'L')
		args->mod_cap_l = 1;
	else if (**format == 'h')
		args->mod_h = 1;
	if (args->mod_l + args->mod_cap_l + args->mod_h == 1)
		*format += 1;
	if (**format == 'l' && args->mod_l == 1)
	{
		args->mod_l = 0;
		args->mod_ll = 1;
		*format += 1;
	}
	else if (**format == 'h' && args->mod_h == 1)
	{
		args->mod_h = 0;
		args->mod_hh = 1;
		*format += 1;
	}
}

/*
** Check the width and precision of the current conversion
*/
static void	ft_check_width_precision(const char **format, t_print *args)
{
	int	nbr;

	nbr = 0;
	while (**format >= '0' && **format <= '9')
	{
		nbr = nbr * 10 + **format - '0';
		*format += 1;
	}
	args->width = nbr;
	nbr = 0;
	if (**format == '.')
	{
		args->dot = 1;
		*format += 1;
		while (**format >= '0' && **format <= '9')
		{
			nbr = nbr * 10 + **format - '0';
			*format += 1;
		}
	}
	args->precision = nbr;
	args->precision2 = nbr;
}

/*
** Check which flags are active for the current conversion.
*/
static int	ft_check_flags(const char **format, t_print *args)
{
	if (**format != '#' && **format != '0' && **format != '-'
		&& **format != '+' && **format != ' ')
		return (0);
	if (**format == '#')
		args->hash = 1;
	else if (**format == '0')
		args->zero = 1;
	else if (**format == '-')
		args->dash = 1;
	else if (**format == '+')
		args->plus = 1;
	else if (**format == ' ')
		args->space = 1;
	return (1);
}

/*
** Function to call the correct conversions.
*/
int	ft_type_conversion(const char **format, t_print *args)
{
	*format += 1;
	ft_initialize_args(args);
	while (ft_check_flags(format, args))
		*format += 1;
	if (args->plus == 1 && args->space == 1)
		args->space = 0;
	if (args->dash == 1 && args->zero == 1)
		args->zero = 0;
	ft_check_width_precision(format, args);
	ft_check_modifier(format, args);
	if (**format == 's' || **format == 'c' || **format == '%')
		ft_cs_conversion(format, args);
	else if (**format == 'd' || **format == 'i' || **format == 'o'
		|| **format == 'p' || **format == 'u' || **format == 'x'
		|| **format == 'X')
		ft_diopux_conversion(format, args);
	else if (**format == 'e' || **format == 'f' || **format == 'g')
		ft_efg_conversion(format, args);
	else if (**format == 'b')
		ft_b_conversion(format, args);
	else
		return (-1);
	return (args->arg_len);
}
