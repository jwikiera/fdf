/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwikiera <jwikiera@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:55:21 by jwikiera          #+#    #+#             */
/*   Updated: 2022/10/17 17:55:22 by jwikiera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_realloc_gnl(void *src, size_t new_len)
{
	size_t	i;
	char	*ptr;
	char	*res;

	res = ft_calloc(1, new_len);
	if (res == NULL)
	{
		free(src);
		return (NULL);
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

int	*ft_realloc_intarr(int *src, size_t arr_size, size_t new_size)
{
	size_t	i;
	int		*res;

	if (new_size <= arr_size)
	{
		free(src);
		return (NULL);
	}
	res = ft_calloc(new_size, sizeof(int));
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		res[i] = src[i];
		i ++;
	}
	free(src);
	return (res);
}

int	**ft_realloc_int2darr(int **src, size_t elem_size, size_t arr_size, size_t new_size)
{
	size_t	i;
	size_t	j;
	int		**res;

	if (new_size <= arr_size)
	{
		j = 0;
		while (j < elem_size)
		{
			free(src[j]);
			j ++;
		}
		free(src);
		return (NULL);
	}
	printf("mallocing %zu times %lu\n", new_size, sizeof(*src));
	res = ft_calloc(new_size, sizeof(*src));
	if (res == NULL)
	{
		j = 0;
		while (j < elem_size)
		{
			free(src[j]);
			j ++;
		}
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		if (i < arr_size)
			res[i] = src[i];
		else
			res[i] = ft_calloc(elem_size, sizeof(**src));
		i ++;
	}
	free(src);
	//free(res[arr_size]);
	//printf("hmmm\n");
	return (res);
}

char	*ft_realloc_chararr(char *src, size_t arr_size, size_t new_size)
{
	size_t	i;
	char	*res;

	if (new_size <= arr_size)
	{
		free(src);
		return (NULL);
	}
	res = ft_calloc(new_size, sizeof(char));
	if (res == NULL)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		res[i] = src[i];
		i ++;
	}
	free(src);
	return (res);
}
