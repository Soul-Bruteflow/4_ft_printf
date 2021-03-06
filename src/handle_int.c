/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvlad <mvlad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:23:20 by mvlad             #+#    #+#             */
/*   Updated: 2017/10/06 17:35:28 by mvlad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_int(t_printf *p)
{
	p->is_signed = true;
	handle_numbers(p);
}
