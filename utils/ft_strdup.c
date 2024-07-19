#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*dest;
	int	i;

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