#include "ft_printf.h"

void	handle_hex_small(t_printf *p)
{
	p->count += ft_print(ft_basification(va_arg(p->args, unsigned int), 16, false));
}