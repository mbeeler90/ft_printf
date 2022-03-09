# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 20:12:34 by manuelbeele       #+#    #+#              #
#    Updated: 2022/03/04 20:05:58 by manuelbeele      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ./sources/ft_printf.c
SRCS += ./sources/utils/ft_type_conversion.c
SRCS += ./sources/utils/ft_set_color.c
SRCS += ./sources/utils/ft_initialize_args.c
SRCS += ./sources/cs_conversion/ft_cs_conversion.c
SRCS += ./sources/diopux_conversion/ft_diopux_conversion.c
SRCS += ./sources/diopux_conversion/ft_di_conversion.c
SRCS += ./sources/diopux_conversion/ft_oux_conversion.c
SRCS += ./sources/diopux_conversion/ft_p_conversion.c
SRCS += ./sources/diopux_conversion/ft_convert_number.c
SRCS += ./sources/diopux_conversion/ft_get_sig_bytes.c
SRCS += ./sources/diopux_conversion/ft_print_width_precision.c
SRCS += ./sources/diopux_conversion/ft_print_number.c
SRCS += ./sources/diopux_conversion/ft_print_dash.c
SRCS += ./sources/efg_conversion/ft_efg_conversion.c
SRCS += ./sources/efg_conversion/ft_f_conversion.c
SRCS += ./sources/efg_conversion/ft_e_conversion.c
SRCS += ./sources/efg_conversion/ft_g_conversion.c
SRCS += ./sources/efg_conversion/ft_print_g_as_e.c
SRCS += ./sources/efg_conversion/ft_convert_float.c
SRCS += ./sources/efg_conversion/ft_printf_lftoa.c
SRCS += ./sources/efg_conversion/ft_f_conversion_number.c
SRCS += ./sources/efg_conversion/ft_f_conversion_frac.c
SRCS += ./sources/efg_conversion/ft_fraction_bintoa.c
SRCS += ./sources/efg_conversion/ft_print_width.c
SRCS += ./sources/efg_conversion/ft_print_hash_dash.c
SRCS += ./sources/b_conversion/ft_b_conversion.c

OBJECTS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -c

all: $(NAME)

/%.o: %.c
	$(CC) $(FLAGS) $<

$(NAME): $(OBJECTS)
	make -C libft
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	make -C libft/ clean
	find ./sources/ -type f -name "*.o" -delete

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
