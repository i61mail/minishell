/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:23:32 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 01:02:49 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_2denv(t_env *envir)
{
	char	**_2denv;
	char	*temp;
	char	*temp1;
	int		i;

	i = 0;
	_2denv = malloc(sizeof(char *) * (ft_env_length(envir) + 1));
	if (!_2denv)
		return (NULL);
	while (envir)
	{
		temp = ft_strjoin(ft_strdup(envir->key), "=");
		temp1 = ft_strjoin(temp, envir->value);
		_2denv[i] = temp1;
		envir = envir->next;
		i++;
	}
	_2denv[i] = NULL;
	return (_2denv);
}

char	**ft_2dcomm(t_list *comm)
{
	char	**_2dcomm;
	int		i;

	i = 0;
	_2dcomm = malloc(sizeof(char *) * (ft_comm_length(comm) + 1));
	if (!_2dcomm)
		return (NULL);
	while (comm && !ft_isred(comm->type))
	{
		_2dcomm[i] = comm->content;
		comm = comm->next;
		i++;
	}
	_2dcomm[i] = NULL;
	return (_2dcomm);
}

t_list	*ft_split_pipe(t_list **new_comm, t_vars *vars)
{
	t_list		*temp;
	t_list		*prev;

	temp = (*new_comm);
	prev = NULL;
	while (temp && temp->type != PIP)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp)
	{
		vars->pipe = 1;
		prev->next = NULL;
		// free pipe node !
		return (temp->next);
	}
	else
	{
		vars->pipe = 0;
		return (NULL);
	}	
}

char	*ft_strchr_2(const char *str, const char *sep)
{
	int i;
	int j;
	int t;

	i = 0;
	if(!str || !sep)
		return (NULL);
	while(str[i])
	{
		t = i;
		j = 0;
		while (str[t++] == sep[j++])
		{
			if (j == ft_strlen((char *)sep))
				return((char *)&str[i]);
		}
		i++;
	}
	return (NULL);

}
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	if(!dst || !src)
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


int	ft_split_2(const char *str, const char *sep, char **k, char **v)
{
	char *found_at;
	
	found_at = ft_strchr_2(str, sep);
	if(!found_at)
		return (-1);
	int	key_size = (found_at - str);
	int	value_size = ft_strlen(found_at + 1);
	*k = malloc(sizeof(char) * key_size + 1);
	*v = malloc(sizeof(char) * value_size + 1);
	ft_strlcpy(*k, str, key_size + 1);
	ft_strlcpy(*v, found_at + ft_strlen((char *)sep), value_size + 1);
    return (0);
}