/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcopakov <hcopakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:35:14 by hcopakov          #+#    #+#             */
/*   Updated: 2024/08/21 18:58:13 by hcopakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	join = malloc(len + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	return (join);
}

void	*ft_memcpy(void *dest, const void *src, size_t n) // memory copy
{
	unsigned char		*temp_d;
	const unsigned char	*temp_s;
	size_t				i;

	temp_d = dest;
	temp_s = src;
	i = 0;
	if (!temp_d && !temp_s)
		return (NULL);
	while (n > 0)
	{
		temp_d[i] = temp_s[i];
		i++;
		n--;
	}
	return (dest);
}

char	*ft_strdup(const char *s) // string duplicates
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n) // string compares
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (n > 0)
		{
			if (((unsigned char)s1[i] != (unsigned char)s2[i])
				|| !(unsigned char)s1[i])
				return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
			i++;
			n--;
		}
	}
	return (0);
}

int	ft_strlen(const char *s) // string length
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
