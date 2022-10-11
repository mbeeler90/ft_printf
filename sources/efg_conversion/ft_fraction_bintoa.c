/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fraction_bintoa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 17:44:01 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	ft_add_bin_strings(char *fraction_bin, char *add_fraction)
{
	int		i;
	int		load;

	i = ft_strlen(fraction_bin);
	load = 0;
	while (--i >= 0)
	{
		if (fraction_bin[i] < add_fraction[i] && load == 0)
			fraction_bin[i] = '1';
		else if (fraction_bin[i] == '1' && add_fraction[i] == '1' && load == 0)
		{
			fraction_bin[i] = '0';
			load = 1;
		}
		else if (fraction_bin[i] == '0' && add_fraction[i] == '0' && load == 1)
		{
			fraction_bin[i] = '1';
			load = 0;
		}
		else if (fraction_bin[i] > add_fraction[i] && load == 1)
			fraction_bin[i] = '0';
	}
}

static void	ft_add_number(char **fraction, char **fraction_bin, int i)
{
	char	*fraction_tmp;
	char	*digit;

	fraction_tmp = ft_strndup(*fraction_bin, i + 1);
	digit = ft_lutoa(ft_bintolu(fraction_tmp));
	ft_strdel(&fraction_tmp);
	if (!*fraction)
		*fraction = ft_strdup(digit);
	else
		ft_strpad_right_inplace(fraction, *digit, 1);
	ft_strdel(&digit);
}

static void	ft_banker_rounding(char **fraction, char **fraction_bin, \
			t_print *args)
{
	int		len;
	char	digit;

	len = ft_strlen(*fraction) - 1;
	if (ft_strlen(*fraction) != 1)
		digit = *(*fraction + len - 1) - '0';
	else
		digit = args->num_uneven;
	if (!ft_strchr(*fraction_bin, '1')
		&& args->precision == 0
		&& *(*fraction + len) == '5'
		&& digit % 2 == 0)
	{
		*(*fraction + len) = '4';
	}
}

static void	ft_add_first_number(char **fraction_bin, const char *fraction_div, \
			char **fraction, t_print *args)
{
	char	*fraction_tmp;
	int		i;

	i = ft_strlen(*fraction_bin) - ft_strlen(fraction_div);
	if (i >= 0)
	{
		ft_add_number(fraction, fraction_bin, i);
		fraction_tmp = *fraction_bin;
		*fraction_bin = ft_strdup(fraction_tmp + i + 1);
		ft_strdel(&fraction_tmp);
		if (!ft_strchr(*fraction_bin, '1') && args->precision > 0)
		{
			ft_strpad_right_inplace(fraction, '0', args->precision);
			args->precision = -1;
		}
		else if (ft_strchr(*fraction_bin, '1'))
			ft_strtrim_char_left_inplace(fraction_bin, '0');
		ft_banker_rounding(fraction, fraction_bin, args);
	}
	else
	{
		fraction_tmp = ft_strdup("0");
		ft_add_number(fraction, &fraction_tmp, 1);
		ft_strdel(&fraction_tmp);
	}
}

/*
** Convert the fraction of the float to a string
*/
char	*ft_fraction_bintoa(const char *binary, const char *fraction_div, \
		t_print *args)
{
	char	*fraction;
	char	*fraction_bin;
	char	*add_fraction;

	fraction_bin = ft_strdup(binary);
	fraction = NULL;
	while (args->precision >= 0)
	{
		add_fraction = ft_strpad_right(fraction_bin, '0', 1);
		ft_strpad_left_inplace(&add_fraction, '0', 3);
		ft_strpad_right_inplace(&fraction_bin, '0', 3);
		ft_strpad_left_inplace(&fraction_bin, '0', 1);
		ft_add_bin_strings(fraction_bin, add_fraction);
		ft_strtrim_char_left_inplace(&fraction_bin, '0');
		ft_add_first_number(&fraction_bin, fraction_div, &fraction, args);
		ft_strdel(&add_fraction);
		args->precision--;
	}
	ft_strdel(&fraction_bin);
	return (fraction);
}
