/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash_dash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:44:29 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** print hash und dash formating
*/
void	ft_print_hash_dash(t_print *args, char *result)
{
	int	len;

	len = ft_strlen(result);
	if (args->hash == 1)
	{
		args->arg_len += write(1, ".", 1);
		len++;
	}
	while (args->width > len + args->sign)
	{
		args->arg_len += write(1, " ", 1);
		args->width--;
	}
}
