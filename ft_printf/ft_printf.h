/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:00:36 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/21 04:47:50 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

# define HEXADECIMAL "0123456789abcdef"
# define HEXADECIMAL_CAP "0123456789ABCDEF"

int		ft_printf(const char *format, ...);
int		ft_format(va_list ap, const char format);
int		my_put_char(char c);
int		my_put_str(char *str);
int		my_put_nbr(int num);
int		my_put_unsigned_nbr(unsigned int num);
int		my_put_hex(unsigned long num, int cap);
int		my_put_pointer(void *ptr);
int		my_put_percent(void);

#endif
