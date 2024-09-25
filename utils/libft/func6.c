/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:53:12 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 17:53:46 by isrkik           ###   ########.fr       */
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
