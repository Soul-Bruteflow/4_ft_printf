#include "ft_printf.h"

void	handle_ulong(t_printf *p)
{
	p->count += ft_print(ft_itoa_long(va_arg(p->args, unsigned long)));
}