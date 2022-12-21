/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:44:05 by jwikiera          #+#    #+#             */
/*   Updated: 2022/11/03 15:44:06 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	clamp_int(int min, int max, int val)
{
	if (val > max)
		return (max);
	else if (val < min)
		return (min);
	else
		return (val);
}

size_t	clamp_size_t(size_t min, size_t max, size_t val)
{
	if (val > max)
		return (max);
	else if (val < min)
		return (min);
	else
		return (val);
}

size_t	ft_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_pow(int a, int b)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i ++;
	}
	return (res);
}
