/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diopux_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/06 12:23:20 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_diopux_conversion(const char **format, t_print *args)
{
	if (**format == 'd' || **format == 'i')
		ft_di_conversion(format, args);
	else if (**format == 'o' || **format == 'u' || **format == 'x'
		|| **format == 'X')
		ft_oux_conversion(format, args);
	else
		ft_p_conversion(format, args);
}
