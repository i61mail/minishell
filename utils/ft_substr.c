/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:57:13 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/08 08:30:03 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start] && len > 0)
	{
		sub[i] = s[start];
		start++;
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}

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
