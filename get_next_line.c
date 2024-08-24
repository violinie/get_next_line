/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanacop <hanacop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:59:31 by hcopakov          #+#    #+#             */
/*   Updated: 2024/08/24 05:39:56 by hanacop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_rest(char *s, char *line)
{
	char	*rest;
	size_t	line_len = ft_strlen(line);

	if (!s || !line)
		return (NULL);
	s += line_len;
	if (*s == '\0')
		return (NULL);
	rest = ft_strdup(s);
	return (rest);
}

char	*get_current_line(char **s)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!s || !*s || **s == '\0')
		return (NULL);
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, *s, i);
	if ((*s)[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	contains_new_line(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	read_and_update_buffer(int fd, char **buf)
{
	char	*recently_read;
	char	*new_buf;
	int		num_bytes_read;

	recently_read = malloc(BUFFER_SIZE + 1);
	if (!recently_read)
		return (-1);
	num_bytes_read = 1;
	while (num_bytes_read > 0)
	{
		num_bytes_read = read(fd, recently_read, BUFFER_SIZE);
		recently_read[num_bytes_read] = '\0';
		if (*buf)
			new_buf = ft_strjoin(*buf, recently_read);
		else
			new_buf = ft_strdup(recently_read);
		free(*buf);
		*buf = new_buf;
		if (contains_new_line(*buf))
			break;
	}
	free(recently_read);
	if (num_bytes_read < 0)
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	return (num_bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	int			num_bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	num_bytes_read = read_and_update_buffer(fd, &buf);
	if (num_bytes_read == -1)
		return (NULL);
	line = get_current_line(&buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	buf = get_rest(buf, line);
	if (!buf && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);


	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);

	close(fd);
	return (0);
}
// gcc -Wall -Wextra -Werror -D -g BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
