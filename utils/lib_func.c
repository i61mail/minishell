/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:56:00 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/10 08:57:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static void	bring_words(const char *s, char c, int *start, int *end)
{
	int	i;

	i = *start;
	while (s[i] == c && s[i] != '\0')
		i++;
	*start = i;
	while (s[i] != c && s[i] != '\0')
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

char	**ft_split(char *s, char c)
{
	int		len_words;
	char	**str;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len_words = count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (len_words + 1));
	if (!str)
		return (NULL);
	start = 0;
	while (i < len_words)
	{
		bring_words(s, c, &start, &end);
		str[i] = ft_substr(s, start, end - start + 1);
		if (!str[i])
			return (free_dom(str, i), NULL);
		i++;
		start = end + 1;
	}
	str[i] = NULL;
	return (str);
}
