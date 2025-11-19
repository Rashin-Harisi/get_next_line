/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:03:12 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/18 13:55:10 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static int	read_handler(int fd, char *buf, int n)
{
	int	sz;

	sz = read(fd, buf, n);
	if (sz >= 0)
		buf[sz] = '\0';
	return (sz);
}

char	*free_and_null_handler(char **buf_s)
{
	if (*buf_s)
		free(*buf_s);
	*buf_s = NULL;
	return (NULL);
}

static char	*buf_s_update_handler(char **buf_s, char *buf, int fd)
{
	int		sz;
	char	*temp;

	sz = 1;
	while (!is_newline_exist(*buf_s) && sz > 0)
	{
		sz = read_handler(fd, buf, BUFFER_SIZE);
		if (sz < 0)
			return (free_and_null_handler(buf_s));
		temp = join_helper(*buf_s, buf);
		if (!temp)
		{
			*buf_s = NULL;
			return (NULL);
		}
		*buf_s = temp;
	}
	if (!(*buf_s) || *(*buf_s) == '\0')
		return (free_and_null_handler(buf_s));
	return (*buf_s);
}

static char	*line_extract_handler(char **buf_s)
{
	char	*line;
	char	*temp;

	line = extract_line_handler(*buf_s);
	if (!line)
	{
		free(*buf_s);
		*buf_s = NULL;
		return (NULL);
	}
	temp = remove_extra_space_handler(*buf_s);
	if (!temp)
	{
		free(line);
		free(*buf_s);
		*buf_s = NULL;
		return (NULL);
	}
	free(*buf_s);
	*buf_s = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*buf_s;
	char		*line;

	if (!buf_s)
		buf_s = NULL;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free_and_null_handler(&buf_s));
	if (!buf_s_update_handler(&buf_s, buf, fd))
	{
		free(buf);
		return (NULL);
	}
	line = line_extract_handler(&buf_s);
	free(buf);
	if (line && *line != '\0')
		return (line);
	return (NULL);
}
