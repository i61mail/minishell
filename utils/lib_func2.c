/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:57:13 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/10 08:57:47 by isrkik           ###   ########.fr       */
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

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*s;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (free(s1), NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	len = ft_strlen(s);
	i = 0;
	while (s2[i] && i < n)
	{
		s[len++] = s2[i];
		i++;
	}
	s[len] = '\0';
	return (free(s1), s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	int		i;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	i = 0;
	len = ft_strlen(str);
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = '\0';
	return (free(s1), str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = (char *)b;
	while (len > 0)
	{
		*s = (unsigned char)c;
		s++;
		len--;
	}
	return (b);
}

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	dest = malloc(i * sizeof(char) + 1);
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
