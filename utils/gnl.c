#include "../minishell.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

int ft2_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft2_newline(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\n')
        i++;
    return (i);
}

char    *ft2_strchr(char *str, int c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (&str[i]);
        i++;
    }
    return (NULL);
}

void    ft2_memset(char *str, int c)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = c;
        i++;
    }
}

char *ft2_strcpy(char *dst, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char *ft2_strdup(char *s)
{
    int i;
    char    *tmp;
    
    i = 0;
    tmp = malloc(sizeof(char) * ft2_strlen(s) + 1);
    if (!tmp)
        return (free(s), NULL);
    while (s[i])
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char *ft2_strjoin(char *s1, char *s2)
{
    int i;
    int len;
    char *temp;

    i = 0;
    if (!s1)
        return (ft2_strdup(s2));
    len = ft2_strlen(s1);
    temp = malloc(sizeof(char) * (len + ft2_strlen(s2) + 1));
    if (!temp)
        return (free(s1), NULL);
    while (s1[i])
    {
        temp[i] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
    {
        temp[len] = s2[i];
        len++;
        i++;
    }
    temp[len] = '\0';
    free(s1);
    return (temp);
}

char *ft2_strnjoin(char *s1, char *s2, int length)
{
    int i;
    char *temp;
    int len;

    i = 0;
    len = ft2_strlen(s1);
    temp = malloc(sizeof(char) * (ft2_strlen(s1) + ft2_strlen(s2) + 1));
    if (!temp)
        return (free(s1), NULL);
    while (s1[i])
    {
        temp[i] = s1[i];
        i++;
    }
    i = 0;
    while (i < length)
    {
        temp[len] = s2[i];
        len++;
        i++;
    }
    temp[len] = '\0';
    free(s1);
    return (temp);
}

/*                main functions                   */


char    *ft2_join(char *line, char *store, char *new_line)
{
    int length;

    if (new_line)
    {
        length = ft2_newline(store) + 1;
        line = ft2_strnjoin(line, store, length);
        if (!line)
            return (NULL);
        ft2_strcpy(store, new_line + 1);
    }
    else
    {
        line = ft2_strjoin(line, store);
        ft2_memset(store, 0);
    }
    return (line);
}

char    *ft2_check(char **line, char **store, int fd)
{
    char    *new_line;
    char    *stock;
    int     bytes;

    stock = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!stock)
        return (NULL);
    while (1)
    {
        bytes = read(fd, stock, BUFFER_SIZE);
        if (bytes < 0)
            return (free(stock), NULL);
        stock[bytes] = '\0';
        *store = ft2_strjoin(*store, stock);
        if (!*store)
            return (free(stock), NULL);
        ft2_memset(stock, 0);
        new_line = ft2_strchr(*store, '\n');
        *line = ft2_join(*line, *store, new_line);
        if (!*line)
            return (free(stock), NULL);
        if (bytes == 0 || new_line)
            break ;
    }
    free(stock);
    return (*line);
}

char    *get_next_line(int fd)
{
    char    *line;
    static char *store;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = malloc(sizeof(char));
    if (!line)
        return (NULL);
    line[0] = '\0';
    line = ft2_check(&line, &store, fd);
    if (!line)
        return (free(line), NULL);
    if (line[0] == '\0')
        return (free(line), NULL);
    return (line);
}
