/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:16 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:18 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	my_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	chr_to_dgt(char c)
{
	return (c - '0');
}

int	whitespace_sign(const char **nptr)
{
	int	sign;

	sign = 1;
	while (my_isspace(*(*nptr)))
		(*nptr)++;
	while (*(*nptr) == '-' || *(*nptr) == '+')
	{
		if (*(*nptr) == '-')
			sign *= -1;
		(*nptr)++;
	}
	return (sign);
}

int	whitespace_sign_limited(const char **nptr)
{
	while (my_isspace(*(*nptr)))
		(*nptr)++;
	if (*(*nptr) == '-')
	{
		(*nptr)++;
		return (-1);
	}
	else if (*(*nptr) == '+')
	{
		(*nptr)++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = whitespace_sign_limited(&nptr);
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + chr_to_dgt(*nptr);
		nptr ++;
	}
	return (res * sign);
}
