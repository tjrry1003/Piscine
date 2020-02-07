/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 00:26:14 by gicho             #+#    #+#             */
/*   Updated: 2020/02/08 00:31:11 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex03.h"

char	*g_prog;
char	*g_hex;
char	*g_buf;
char	*g_buf_prev;
int		g_duplicated;
int		g_offset;
int		g_cnt;
int		g_is_on_flag_c;
int		g_last_lines;

int		ft_is_equal(char *a, char *b)
{
	int i;

	i = -1;
	while (++i < 16)
		if (a[i] != b[i])
			return (0);
	return (1);
}

void	print(void)
{
	g_last_lines = 1;
	if (ft_is_equal(g_buf, g_buf_prev))
	{
		if (!g_duplicated)
		{
			g_duplicated = 1;
			ft_putstr("*\n");
		}
	}
	else
	{
		g_duplicated = 0;
		print_row(g_offset, g_cnt);
		free(g_buf_prev);
		g_buf_prev = g_buf;
		g_buf = (char*)malloc(17);
	}
	g_offset += 16;
	g_cnt = 0;
}

void	hexdump_stdin(void)
{
	while (read(0, &g_buf[g_cnt], 1))
		if (++g_cnt == 16)
			print();
}

void	hexdump_files(int argc, char *argv[])
{
	int i;
	int fd;

	i = g_is_on_flag_c;
	while (++i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) == -1)
		{
			print_error_msg(argv[i]);
			continue;
		}
		while (read(fd, &g_buf[g_cnt], 1))
		{
			if (errno)
			{
				print_error_msg(argv[i]);
				break ;
			}
			if (++g_cnt == 16)
				print();
		}
	}
}

void	init_other_g_vars(void)
{
	g_hex = "0123456789abcdef";
	g_is_on_flag_c = 0;
	g_last_lines = 0;
	g_offset = 0;
	g_cnt = 0;
	g_duplicated = 0;
	g_buf_prev = (char*)malloc(17);
	g_buf = (char*)malloc(17);
}

int		main(int argc, char *argv[])
{
	g_prog = argv[0];
	init_other_g_vars();
	if (argc >= 2 && is_flag_c(argv[1]))
		g_is_on_flag_c = 1;
	if (argc == 1 + g_is_on_flag_c)
		hexdump_stdin();
	else
		hexdump_files(argc, argv);
	if (g_last_lines)
	{
		if (g_cnt)
			print_row(g_offset, g_cnt);
		print_input_offset(7, g_offset + g_cnt);
		ft_putchar('\n');
	}
	free(g_buf);
	return (0);
}
