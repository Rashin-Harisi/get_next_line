/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:40:24 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/18 13:33:04 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

static void	create_first_node(t_fd **fd_list, int fd)
{
	if (*fd_list == NULL)
	{
		*fd_list = malloc(sizeof(t_fd));
		if (!*fd_list)
			return ;
		(*fd_list)->fd = fd;
		(*fd_list)->buf_s = NULL;
		(*fd_list)->next = NULL;
	}
}

static void	delete_fd_node(t_fd **fd_list, int fd)
{
	t_fd	*curr;
	t_fd	*prev;

	prev = NULL;
	curr = *fd_list;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*fd_list = curr->next;
			if (curr->buf_s)
				free(curr->buf_s);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static t_fd	*find_the_node_helper(t_fd **fd_list, int fd)
{
	t_fd	*node;

	node = *fd_list;
	while (node)
	{
		if (node->fd == fd)
			break ;
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node->fd != fd)
	{
		node->next = malloc(sizeof(t_fd));
		if (!node->next)
			return (NULL);
		node = node->next;
		node->fd = fd;
		node->buf_s = NULL;
		node->next = NULL;
	}
	return (node);
}

static char	*line_reading_handler(t_fd **node, char *buf,
	int fd, t_fd **fd_list)
{
	char	*line;
	int		sz;

	while (!is_newline_exist((*node)->buf_s))
	{
		sz = read(fd, buf, BUFFER_SIZE);
		if (sz <= 0)
		{
			if (sz == 0 && ((*node)->buf_s && *(*node)->buf_s))
				break ;
			return (delete_fd_node(fd_list, fd), NULL);
		}
		buf[sz] = '\0';
		(*node)->buf_s = join_helper((*node)->buf_s, buf);
		if (!(*node)->buf_s)
			return (delete_fd_node(fd_list, fd), NULL);
	}
	if (!(*node)->buf_s || (*node)->buf_s[0] == '\0')
		return (delete_fd_node(fd_list, fd), NULL);
	line = extract_line_handler((*node)->buf_s);
	(*node)->buf_s = remove_extra_space_handler((*node)->buf_s);
	if (!line || !(*node)->buf_s)
		return (free(line), delete_fd_node(fd_list, fd), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fd	*fd_list;
	t_fd		*node;
	char		*buf;
	char		*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		if (fd_list)
			delete_fd_node(&fd_list, fd);
		return (NULL);
	}
	create_first_node(&fd_list, fd);
	if (!fd_list)
		return (free(buf), NULL);
	node = find_the_node_helper(&fd_list, fd);
	if (!node)
		return (free(buf), NULL);
	line = line_reading_handler(&node, buf, fd, &fd_list);
	free(buf);
	if (line && *line != '\0')
		return (line);
	return (NULL);
}
