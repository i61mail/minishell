/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:37 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 16:48:01 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	count_words(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]) && str[i])
			i++;
		if (!ft_isspace(str[i]) && str[i])
			count++;
		while (!ft_isspace(str[i]) && str[i])
			i++;
	}
	return (count);
}

static void	bring_words(const char *s, int *start, int *end)
{
	int	i;

	i = *start;
	while (ft_isspace(s[i]) && s[i] != '\0')
		i++;
	*start = i;
	while (!ft_isspace(s[i]) && s[i] != '\0')
		i++;
	*end = i - 1;
}

static void	free_dom(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split_space(char *s)
{
	int		len_words;
	char	**str;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len_words = count_words(s);
	str = (char **)malloc(sizeof(char *) * (len_words + 1));
	if (!str)
		return (NULL);
	start = 0;
	while (i < len_words)
	{
		bring_words(s, &start, &end);
		str[i] = ft_substr(s, start, end - start + 1);
		if (!str[i])
			return (free_dom(str, i), NULL);
		i++;
		start = end + 1;
	}
	str[i] = NULL;
	return (str);
}
