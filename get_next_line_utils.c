/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:58:06 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/08/16 20:33:03 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i <= len_s1)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= len_s2)
	{
		join[i + len_s1] = s2[i];
		i++;
	}
	join[len_s1 + len_s2 + 1] = '\0';
	return (join);
}

char	*ft_strdup(const char *s1) {
	char	*dup;
	size_t		len;
	size_t		i;

	len = ft_strlen(s1);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;
	i = 0;
	while (i < len) {
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return dup;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
