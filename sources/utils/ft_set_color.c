/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 16:21:24 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** Set the simple color.
*/
static int	ft_color(const char **format)
{
	int	len;

	len = 0;
	if (!ft_strncmp(*format, "{BLACK}", 7))
		len = write(1, "\e[0;30m", 7);
	else if (!ft_strncmp(*format, "{RED}", 5))
		len = write(1, "\e[0;31m", 7);
	else if (!ft_strncmp(*format, "{GREEN}", 7))
		len = write(1, "\e[0;32m", 7);
	else if (!ft_strncmp(*format, "{YELLOW}", 8))
		len = write(1, "\e[0;33m", 7);
	else if (!ft_strncmp(*format, "{BLUE}", 6))
		len = write(1, "\e[0;34m", 7);
	else if (!ft_strncmp(*format, "{PURPLE}", 8))
		len = write(1, "\e[0;35m", 7);
	else if (!ft_strncmp(*format, "{CYAN}", 6))
		len = write(1, "\e[0;36m", 7);
	else if (!ft_strncmp(*format, "{WHITE}", 7))
		len = write(1, "\e[0;37m", 7);
	if (len)
		*format += ft_strchrloc(*format, '}') + 1;
	return (len);
}

/*
** Set the bold color
*/
static int	ft_bold(const char **format)
{
	int	len;

	len = 0;
	if (!ft_strncmp(*format, "{BLACK_BD}", 10))
		len = write(1, "\e[1;30m", 7);
	else if (!ft_strncmp(*format, "{RED_BD}", 8))
		len = write(1, "\e[1;31m", 7);
	else if (!ft_strncmp(*format, "{GREEN_BD}", 10))
		len = write(1, "\e[1;32m", 7);
	else if (!ft_strncmp(*format, "{YELLOW_BD}", 11))
		len = write(1, "\e[1;33m", 7);
	else if (!ft_strncmp(*format, "{BLUE_BD}", 9))
		len = write(1, "\e[1;34m", 7);
	else if (!ft_strncmp(*format, "{PURPLE_BD}", 11))
		len = write(1, "\e[1;35m", 7);
	else if (!ft_strncmp(*format, "{CYAN_BD}", 9))
		len = write(1, "\e[1;36m", 7);
	else if (!ft_strncmp(*format, "{WHITE_BD}", 10))
		len = write(1, "\e[1;37m", 7);
	if (len)
		*format += ft_strchrloc(*format, '}') + 1;
	return (len);
}

/*
** Set the underline color
*/
static int	ft_underline(const char **format)
{
	int	len;

	len = 0;
	if (!ft_strncmp(*format, "{BLACK_UL}", 10))
		len = write(1, "\e[4;30m", 7);
	else if (!ft_strncmp(*format, "{RED_UL}", 8))
		len = write(1, "\e[4;31m", 7);
	else if (!ft_strncmp(*format, "{GREEN_UL}", 10))
		len = write(1, "\e[4;32m", 7);
	else if (!ft_strncmp(*format, "{YELLOW_UL}", 11))
		len = write(1, "\e[4;33m", 7);
	else if (!ft_strncmp(*format, "{BLUE_UL}", 9))
		len = write(1, "\e[4;34m", 7);
	else if (!ft_strncmp(*format, "{PURPLE_UL}", 11))
		len = write(1, "\e[4;35m", 7);
	else if (!ft_strncmp(*format, "{CYAN_UL}", 9))
		len = write(1, "\e[4;36m", 7);
	else if (!ft_strncmp(*format, "{WHITE_UL}", 10))
		len = write(1, "\e[4;37m", 7);
	if (len)
		*format += ft_strchrloc(*format, '}') + 1;
	return (len);
}

/*
** Set background color
*/
static int	ft_background(const char **format)
{
	int	len;

	len = 0;
	if (!ft_strncmp(*format, "{BLACK_BG}", 10))
		len = write(1, "\e[40m", 5);
	else if (!ft_strncmp(*format, "{RED_BG}", 8))
		len = write(1, "\e[41m", 5);
	else if (!ft_strncmp(*format, "{GREEN_BG}", 10))
		len = write(1, "\e[42m", 5);
	else if (!ft_strncmp(*format, "{YELLOW_BG}", 11))
		len = write(1, "\e[43m", 5);
	else if (!ft_strncmp(*format, "{BLUE_BG}", 9))
		len = write(1, "\e[44m", 5);
	else if (!ft_strncmp(*format, "{PURPLE_BG}", 11))
		len = write(1, "\e[45m", 5);
	else if (!ft_strncmp(*format, "{CYAN_BG}", 9))
		len = write(1, "\e[46m", 5);
	else if (!ft_strncmp(*format, "{WHITE_BG}", 10))
		len = write(1, "\e[47m", 5);
	if (len)
		*format += ft_strchrloc(*format, '}') + 1;
	return (len);
}

/*
** Function to set the color and type of the text.
*/
int	ft_set_color(const char **format)
{
	if (!ft_strncmp(*format, "{EOC}", 5))
	{
		*format += 5;
		return (write(1, "\e[0m", 4));
	}
	else if (ft_strnstr(*format, "_BD", ft_strchrloc(*format, '}')))
		return (ft_bold(format));
	else if (ft_strnstr(*format, "_UL", ft_strchrloc(*format, '}')))
		return (ft_underline(format));
	else if (ft_strnstr(*format, "_BG", ft_strchrloc(*format, '}')))
		return (ft_background(format));
	else
		return (ft_color(format));
}
