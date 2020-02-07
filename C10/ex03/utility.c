/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 00:29:43 by gicho             #+#    #+#             */
/*   Updated: 2020/02/08 00:30:07 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex03.h"

int		is_printable(unsigned char c)
{
	return (' ' <= c && c <= '~');
}

void	ft_putchar(unsigned char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*(str++));
}

int		is_flag_c(char *str)
{
	return (str[0] == '-' && str[1] == 'C');
}
