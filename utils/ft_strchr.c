/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:30:37 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/25 14:54:22 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	chr;

	chr = (unsigned char )c;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == chr)
			return ((char *)&str[i]);
		i++;
	}
	if (str && str[i] == chr)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strstr(char *str, char *to_find, int *b)
{
	int i = 0;
	int h = 0;
	int j = 0;
	
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
