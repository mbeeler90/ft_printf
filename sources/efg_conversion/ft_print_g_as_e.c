/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_g_as_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/03/04 15:14:20 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_format_e(char **result)
{
	char	*new_result;

	if (ft_strlen(*result) > 1 && *(*result + 1) != '.')
	{
		if (!ft_strchr(*result, '.'))
			ft_strtrim_char_right_inplace(result, '0');
		else
		{
			new_result = *result;
			*(new_result + 1) = '.';
			*(new_result + 2) = '0';
			*result = ft_strndup(new_result, ft_strlen(new_result) - 1);
			ft_strdel(&new_result);
		}
	}
}

static void	ft_finalize_e(char **result, t_print *args, int g)
{
	char	*new_result;

	if (ft_strchr(*result, '.') && args->hash == 0)
		ft_strtrim_char_right_inplace(result, '0');
	if (*(*result + ft_strlen(*result) - 1) == '.' && args->hash == 0)
		ft_strtrim_char_right_inplace(result, '.');
	else if (!ft_strchr(*result, '.') && args->hash == 1)
		ft_strpad_right_inplace(result, '.', 1);
	args->hash = 0;
	ft_strpad_right_inplace(result, 'e', 1);
	new_result = ft_itoa(g);
	if (*new_result != '-')
		ft_strpad_left_inplace(&new_result, '+', 1);
	if (ft_strlen(new_result) == 2)
	{
		ft_strpad_right_inplace(&new_result, '0', 1);
		*(new_result + 2) = *(new_result + 1);
		*(new_result + 1) = '0';
	}
	ft_strjoin_inplace(result, &new_result);
}

void	ft_print_g_as_e(char **result, t_print *args, int i, int g)
{
	char	*new_result;

	new_result = *result;
	*result = ft_strndup(new_result + i, 1);
	ft_strpad_right_inplace(result, '.', 1);
	while (args->precision2 > 0)
	{
		i++;
		if (*(new_result + i) != '.')
		{
			ft_strpad_right_inplace(result, *(new_result + i), 1);
			args->precision2--;
		}
	}
	ft_strdel(&new_result);
	ft_round_string_inplace(result);
	ft_format_e(result);
	ft_finalize_e(result, args, g);
}
