/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:55:21 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 17:55:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, ssize_t new_len)
{
	size_t	i;
	char	*ptr;
	char	*res;

	res = malloc(new_len);
	if (res == NULL)
	{
		free(src);
		return (0);
	}
	i = 0;
	ptr = src;
	while (i < sizeof(src))
	{
		*(res + i) = *(ptr + i);
		i ++;
	}
	free(src);
	return (res);
}
