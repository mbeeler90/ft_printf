/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 16:15:55 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Write the current character if it not a conversion, convert if it is.
*/
static int	ft_iterate_format(const char **format, t_print *args)
{
	int	conversion;
	int	len;

	len = 0;
	if (**format == '{' && ft_strchr(*format, '}'))
		len += ft_set_color(format);
	if (**format != '%')
		len += write(1, *format, 1);
	else
	{
		conversion = ft_type_conversion(format, args);
		if (conversion == -1)
			len = -1;
		else
			len += conversion;
	}
	if (**format)
		*format += 1;
	return (len);
}

/*
** Iterate through the string that is given as input and printing the characters
** and conversions.
*/
int	ft_printf(const char *format, ...)
{
	t_print	*args;
	int		len;
	int		conversion;

	len = 0;
	conversion = 0;
	args = (t_print *)malloc(sizeof(t_print));
	if (!args)
		return (-1);
	va_start(args->ap, format);
	while (*format && conversion != -1)
	{
		conversion = ft_iterate_format(&format, args);
		if (conversion != -1)
			len += conversion;
	}
	va_end(args->ap);
	free(args);
	return (len);
}
