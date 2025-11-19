/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:03:33 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/18 12:22:17 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	is_newline_exist(char *buf)
{
	int	i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

char	*join_helper(char *buf_s, char *buf)
{
	char	*new;
	int		i;
	int		j;

	if (!buf_s)
	{
		buf_s = malloc(1 * sizeof(char));
		if (!buf_s)
			return (NULL);
		buf_s[0] = '\0';
	}
	new = malloc((ft_strlen(buf) + ft_strlen(buf_s) + 1) * sizeof(char));
	if (!new)
		return (free_and_null_handler(&buf_s));
	j = -1;
	while (buf_s[++j] != '\0')
		new[j] = buf_s[j];
	i = 0;
	while (buf[i] != '\0')
		new[j++] = buf[i++];
	new[j] = '\0';
	free(buf_s);
	return (new);
}

char	*remove_extra_space_handler(char *buf)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	new = malloc((ft_strlen(buf + i) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (buf[i] != '\0')
		new[j++] = buf[i++];
	new[j] = '\0';
	return (new);
}

char	*extract_line_handler(char *buf_s)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buf_s || buf_s[0] == '\0')
		return (NULL);
	while (buf_s[i] != '\0' && buf_s[i] != '\n')
		i++;
	if (buf_s[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buf_s[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}
