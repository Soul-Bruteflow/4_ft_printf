/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 12:40:07 by mvlad             #+#    #+#             */
/*   Updated: 2017/10/06 15:31:30 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_escape(t_printf *p)
{
	if (p->format[p->i] != '\0')
	{
		if (p->got_width && !p->flags.minus)
			p->count += print_prefix_pad(1, p->width,
			(char)(p->flags.zero ? '0' : ' '));
		if (p->format[p->i] && p->i <= ft_strlen(p->format) && p->i != '\0')
		{
			write(1, &p->format[p->i], 1);
			p->i++;
			p->count++;
		}
		if (p->got_width && p->flags.minus)
			p->count += print_prefix_pad(1, p->width, ' ');
		while (p->format[p->i] && p->i <= ft_strlen(p->format) && p->i != '\0')
		{
			write(1, &p->format[p->i], 1);
			p->i++;
			p->count++;
		}
	}
}

void	parse_core(t_printf *p)
{
	t_bool not_spec;

	p->i++;
	while (!ft_isconversion_char(p->format, p->i) && p->i <= ft_strlen(p->format) && p->format[p->i] != '\0')
	{
		not_spec = false;
		if (ft_isflag(p->format, p->i))
		{
			parse_flags(p);
			not_spec = true;
		}
		if (ft_isdigit(p->format[p->i]))
		{
			parse_width(p);
			not_spec = true;
		}
		if (p->format[p->i] == '.')
		{
			parse_precision(p);
			not_spec = true;
		}
		if (ft_islength(p->format, p->i))
		{
			parse_length(p);
			not_spec = true;
		}
		if (!not_spec)
		{
			if (p->i <= ft_strlen(p->format) && p->format[p->i] != '\0')
				exit(1);
		}
	}
	if (ft_isconversion_char(p->format, p->i))
	{
		p->conv_char = (unsigned char)p->format[p->i];
		(p->handlers[p->conv_char])(p);
	}
	else
		handle_escape(p);
}

ssize_t	walk_format(t_printf *p)
{
	while (p->format[p->i] && p->i <= ft_strlen(p->format))
	{
		if (p->format[p->i] == '%')
		{
			default_handler_format(p);
			parse_core(p);
		}
		else if (p->i <= ft_strlen(p->format))
		{
			write(1, &p->format[p->i], 1);
			p->count++;
		}
		p->i++;
	}
	return (p->count);
}

int		ft_printf(const char *format, ...)
{
	t_printf	*p;

	if (!(p = init_printf(format)))
		return (0);
	if (format)
	{
		va_start(p->args, format);
		p->count = walk_format(p);
		va_end(p->args);
	}
	return ((int)p->count);
}
