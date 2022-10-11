/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:43:19 by mbeeler           #+#    #+#             */
/*   Updated: 2022/10/11 16:17:51 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include "../includes/ft_printf.h"

static int	ft_compare_files(FILE *fp1, FILE *fp2)
{
    char	ch1;
    char	ch2;
    int		error;

	ch1 = getc(fp1);
	ch2 = getc(fp2);
	error = 0;
    while (ch1 != EOF && ch2 != EOF)
    {
        if (ch1 != ch2)
            error++;
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }
	return (error);
}

static void	ft_write_file(FILE *fp)
{
    char	ch;

	rewind(fp);
	ch = getc(fp);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fp);
    }
}

static int	ft_run_test(int type, char *str, void *test, void *test2, FILE *fp1, FILE *fp2, int *count)
{
	int		ret_sys;
	int		ret_own;

	freopen("./sys.txt", "w", stdout);
	if (type == 1)
		ret_sys = printf(str, *((char*)test), *((char*)test2));
	else if (type == 2)
		ret_sys = printf(str, (char*)test, (char*)test2);
	else if (type == 3)
		ret_sys = printf("%%, %4%, %.8%, % 3%, %-12%, %05%");
	else if (type == 4)
		ret_sys = printf(str, *((int*)test), *((int*)test2));
	else if (type == 5)
		ret_sys = printf(str, *((t_s16*)test), *((t_s16*)test2));
	else if (type == 6)
		ret_sys = printf(str, *((t_s8*)test), *((t_s8*)test2));
	else if (type == 7)
		ret_sys = printf(str, *((t_s64*)test), *((t_s64*)test2));
	else if (type == 8)
		ret_sys = printf(str, *((t_u32*)test), *((t_u32*)test2));
	else if (type == 9)
		ret_sys = printf(str, *((t_u16*)test), *((t_u16*)test2));
	else if (type == 10)
		ret_sys = printf(str, *((t_u8*)test), *((t_u8*)test2));
	else if (type == 11)
		ret_sys = printf(str, *((t_u64*)test), *((t_u64*)test2));
	else if (type == 12)
		ret_sys = printf(str, test, test2);
	else if (type == 13)
		ret_sys = printf(str, *((t_f64*)test), *((t_f64*)test2));
	else if (type == 14)
		ret_sys = printf(str, *((t_f128*)test), *((t_f128*)test2));
	freopen("./own.txt", "w", stdout);
	if (type == 1)
		ret_own = ft_printf(str, *((char*)test), *((char*)test2));
	else if (type == 2)
		ret_own = ft_printf(str, (char*)test, (char*)test2);
	else if (type == 3)
		ret_own = ft_printf("%%, %4%, %.8%, % 3%, %-12%, %05%");
	else if (type == 4)
		ret_own = ft_printf(str, *((int*)test), *((int*)test2));
	else if (type == 5)
		ret_own = ft_printf(str, *((t_s16*)test), *((t_s16*)test2));
	else if (type == 6)
		ret_own = ft_printf(str, *((t_s8*)test), *((t_s8*)test2));
	else if (type == 7)
		ret_own = ft_printf(str, *((t_s64*)test), *((t_s64*)test2));
	else if (type == 8)
		ret_own = ft_printf(str, *((t_u32*)test), *((t_u32*)test2));
	else if (type == 9)
		ret_own = ft_printf(str, *((t_u16*)test), *((t_u16*)test2));
	else if (type == 10)
		ret_own = ft_printf(str, *((t_u8*)test), *((t_u8*)test2));
	else if (type == 11)
		ret_own = ft_printf(str, *((t_u64*)test), *((t_u64*)test2));
	else if (type == 12)
		ret_own = ft_printf(str, test, test2);
	else if (type == 13)
		ret_own = ft_printf(str, *((t_f64*)test), *((t_f64*)test2));
	else if (type == 14)
		ret_own = ft_printf(str, *((t_f128*)test), *((t_f128*)test2));
	freopen ("/dev/tty", "a", stdout);
	if (ft_compare_files(fp1, fp2) || ret_sys != ret_own)
	{
		printf("\e[31mx(%d)\e[0m ", *count + 1);
		freopen("./error.txt", "a", stdout);
		if (*count == 0)
			printf("c Test errors:\n\n");
		printf("#%d: %s\n", *count + 1, str);
		printf("sys: %d, ", ret_sys);
		ft_write_file(fp1);
		printf("\n");
		printf("own: %d, ", ret_own);
		ft_write_file(fp2);
		printf("\n\n");
		freopen ("/dev/tty", "a", stdout);
		*count += 1;
		return (1);
	}
	else
	{
		printf("\e[32m\xE2\x9C\x93\e[0m ");
		return (1);
	}
}

int	main(int argc, char **argv)
{
	int		total_count;
	int		total_fail;
	int		count;
	int		i;
    FILE	*fp1;
    FILE 	*fp2;
  
	if (argc > 2 || (argc == 2 && (strcmp(argv[1], "mand") && strcmp(argv[1], "bonus"))))
	{
		printf("usage: ./a.out mand / bonus\n");
		return (0);
	}
	total_count = 0;
	total_fail = 0;
	fp1 = fopen("./sys.txt", "r");
	fp2 = fopen("./own.txt", "r");
    if (fp1 == NULL || fp2 == NULL)
    {
		printf("Error : Files not open\n");
    	return (0);
    }

	freopen("./error.txt", "w", stdout);
	printf("");
	freopen ("/dev/tty", "w", stdout);

	if (argc == 1 || !strcmp(argv[1], "mand"))
	{
		printf("c TESTS:\n");
		char	char_test[5] = "\0a\nc\\";
		char	char_test2[5] = "x\tuq\v";
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(1, "%c%8c", char_test + i, char_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(1, "%-8c%-8.4c", char_test + i, char_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(1, "%#3.7c%+10.0c", char_test + i, char_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("s TESTS:\n");
		char	*str_test[5];
		str_test[0] = "a\nc\\";
		str_test[1] = NULL;
		str_test[2] = "test";
		str_test[3] = "";
		str_test[4] ="\0";
		char	*str_test2[5];
		str_test2[0] = "randoooojsdjfjalskfjlasjfkajsfjslkfjasklfjklasjfsdklfkldsfjklds";
		str_test2[1] = (char*)NULL;
		str_test2[2] = "testtttttttttttttttttttttttttttttttttttttttttttttttttttt";
		str_test2[3] = "\n\\\\\\\\\\\\\\";
		str_test2[4] ="--d------d--           ";
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(2, "%s%20s", str_test + i, str_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(2, "%-8s%-8.4s", str_test + i, str_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(2, "%#3.7s%+10.0s", str_test + i, str_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");
		
		printf("%% TESTS:\n");
		count = 0;
		total_count += ft_run_test(3, "%%, %4%, %.8%, % 3%, %-12%, %05%", NULL, NULL, fp1, fp2, &count);
		total_fail += count;
		printf("\n\n");


		printf("d TESTS:\n");
		t_s64	d_test[5];
		d_test[0] = -128;
		d_test[1] = 0;
		d_test[2] = INT32_MAX;
		d_test[3] = INT32_MIN;
		d_test[4] =INT64_MIN;
		t_s64	d_test2[5];
		d_test2[0] = 127;
		d_test2[1] = 899879789279472983;
		d_test2[2] = -1308875585857757;
		d_test2[3] = INT64_MAX;
		d_test2[4] = 0;
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(4, "%0d%.d", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(4, "%5.0d%-+10.6d", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(5, "%0 10hd%-.9hd", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(6, "%0.0hhd%+3.2hhd", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(7, "%#3.5ld%-200ld", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(7, "%0+1.2lld%2.1lld", d_test + i, d_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("i TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(4, "%0i%.i", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(4, "%5.0i%-+10.6i", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(5, "%0 10hd%-.9hi", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(6, "%0.0hhd%+3.2hhi", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(7, "%#3.5ld%-200li", d_test + i, d_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(7, "%0+1.2lld%2.1lli", d_test + i, d_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("u TESTS:\n");
		t_u64	u_test[5];
		u_test[0] = 256;
		u_test[1] = 0;
		u_test[2] = UINT32_MAX;
		u_test[3] = UINT8_MAX;
		u_test[4] =UINT16_MAX;
		t_u64	u_test2[5];
		u_test2[0] = 255;
		u_test2[1] = 899879789279472983;
		u_test2[2] = 1308875585857757;
		u_test2[3] = UINT64_MAX;
		u_test2[4] = 0;
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(8, "%0u%.u", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%5.0u%-+10.6u", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%0 10hu%-.9hu", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(10, "%0.0hhu%+3.2hhu", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%#3.5lu%-200lu", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%0+1.2llu%2.1llu", u_test + i, u_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("o TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(8, "%0o%.o", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%5.0o%-+10.6o", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%0 10ho%-.9ho", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(10, "%0.0hho%+3.2hho", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%#3.5lo%-200lo", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%0+1.2llo%#2.1llo", u_test + i, u_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("x TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(8, "%0x%.x", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%5.0x%-+10.6x", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%0 10hx%-.9hx", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(10, "%0.0hhx%+3.2hhx", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%#3.5lx%-200lx", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%0+1.2llx%#2.1llx", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#10.5x%10.5x", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%#-10.5hx%#.5hx", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#10x%#8.3x", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#8.4x%#8.5x", u_test + i, u_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("X TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(8, "%0X%.X", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%5.0X%-+10.6X", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%0 10hX%-.9hX", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(10, "%0.0hhX%+3.2hhX", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%#3.5lX%-200lX", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(11, "%0+1.2llX%#2.1llX", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#10.5X%10.5X", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(9, "%#-10.5hX%#.5hX", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#10X%#8.3X", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(8, "%#8.4X%#8.5X", u_test + i, u_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("p TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 5)
		{
			total_count += ft_run_test(12, "%0p%.p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%5.0p%-+10.6p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%0 10p%-.9p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%0.0p%+3.2p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%#3.5p%-200p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%0+1.2p%#2.1p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%#10.5p%10.5p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%#-10.5p%#.5p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%#10p%#8.3p", u_test + i, u_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(12, "%#8.4p%#8.5p", u_test + i, u_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("f TESTS:\n");
		t_f128	f_test[8];
		f_test[0] = 0.0;
		f_test[1] = 1.5;
		f_test[2] = 1.4999;
		f_test[3] = 2.5;
		f_test[4] = INFINITY;
		f_test[5] = __FLT_MAX__;
		f_test[6] = __FLT_MIN_10_EXP__;
		f_test[7] = 23.88799;
		t_f128	f_test2[8];
		f_test2[0] = NAN;
		f_test2[1] = -INFINITY;
		f_test2[2] = 3143534.09485345983;
		f_test2[3] = 39045823904589023485293904580949058.0;
		f_test2[4] = -9348534890583940853408878239587824023.0;
		f_test2[5] = __FLT_MAX_EXP__;
		f_test2[6] = __FLT_MIN__;
		f_test2[7] = -0.00000000000000000000000000000001;
		i = -1;
		count = 0;
		while (++i < 8)
		{
			total_count += ft_run_test(13, "%0f%.f", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%5.0f%-+10.6f", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0 10f%-.9f", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0.0lf%+3.2lf", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#3.5lf%-200lf", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%0+1.2Lf%2.1Lf", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%#10.5Lf%10.5Lf", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#-10.5f%#.5f", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#10f%#8.3f", f_test + i, f_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#8.4f%#8.5f", f_test + i, f_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

	}
	if (argc == 1 || !strcmp(argv[1], "bonus"))
	{
		printf("g TESTS:\n");
		t_f128	g_test[8];
		g_test[0] = 0.0;
		g_test[1] = 0.4;
		g_test[2] = 1020;
		g_test[3] = -1020.00001;
		g_test[4] = INFINITY;
		g_test[5] = __FLT_MAX__;
		g_test[6] = __FLT_MIN_10_EXP__;
		g_test[7] = -0.000000000000001;
		t_f128	g_test2[8];
		g_test2[0] = -INFINITY;
		g_test2[1] = 72.4;
		g_test2[2] = 0;
		g_test2[3] = 39045823904589023485293904580949058.0;
		g_test2[4] = -9348534890583940853408878239587824023.0;
		g_test2[5] = __FLT_MAX_EXP__;
		g_test2[6] = __FLT_MIN__;
		g_test2[7] = -0.00000000000000000000000000000001;
		i = -1;
		count = 0;
		while (++i < 8)
		{
			total_count += ft_run_test(13, "%0g%.g", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%5.0g%-+10.6g", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0 10g%-.9g", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0.0lg%+3.2lg", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#3.5lg%-200lg", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%0+1.2Lg%2.1Lg", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%#10.5Lg%10.5Lg", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#-10.5g%#.5g", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#10g%#8.3g", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#8.4g%#8.5g", g_test + i, g_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("e TESTS:\n");
		i = -1;
		count = 0;
		while (++i < 8)
		{
			total_count += ft_run_test(13, "%0e%.e", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%5.0e%-+10.6e", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0 10e%-.9e", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%0.0le%+3.2le", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#3.5le%-200le", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%0+1.2Le%2.1Le", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(14, "%#10.5Le%10.5Le", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#-10.5e%#.5e", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#10e%#8.3e", g_test + i, g_test2 + i, fp1, fp2, &count);
			total_count += ft_run_test(13, "%#8.4e%#8.5e", g_test + i, g_test2 + i, fp1, fp2, &count);
		}
		total_fail += count;
		printf("\n\n");

		printf("b TESTS:\n");
		ft_printf("%-20.6b\n%010hhb\n%010hb\n%.8lb\n%-.9llb", (t_u32)7, (t_u8)100, (t_u16)1000, (t_u64)1000000, (t_u64)1000000000000);
		printf("\n\n");
		
		printf("color TESTS:\n");
		ft_printf("{RED}%s\n{GREEN_BG}%s\n{BLUE_BD}%s\n{YELLOW_UL}%s\n{EOC}%s\n", "start\n", "next line\n", "in the middle\n", "almost done\n", "it's over\n");
		printf("\n\n");
	}
	fclose(fp1);
    fclose(fp2);

	printf("Passed %d of %d tests\n\n", total_count - total_fail, total_count);
	system("leaks a.out");
	return (0);
}
