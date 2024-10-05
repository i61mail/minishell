/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:53:12 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 14:58:29 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_vars(int *i, int *h, int *j)
{
	*i = 0;
	*h = 0;
	*j = 0;
}

char	*ft_strstr(char *str, char *to_find, int *b)
{
	int	i;
	int	h;
	int	j;

	init_vars(&i, &h, &j);
	while (str[i])
	{
		while (ft_isspace(str[i]))
		{
			h = 1;
			i++;
		}
		if (h == 1)
		{
			*b = i;
			h = 0;
		}
		i++;
	}
	if (str[i] == '\0')
		j = i - 1;
	free(to_find);
	to_find = ft_substr(str, *b, j);
	return (to_find);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	if (!dst || !src)
		return (-1);
	srclen = ft_strlen((char *)src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

int	ft_isred(int t)
{
	if (t == RED_IN || t == RED_OUT || t == RED_APPEND || t == HEREDOC)
		return (1);
	return (0);
}

int	ft_overflow(long long *a, long long b)
{
	if (b < *a)
		return (1);
	*a = b;
	return (0);
}
