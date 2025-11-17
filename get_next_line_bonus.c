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

// deleting nof, because reading function reached at the end or get errors
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
			else //means it is the first node, so address of next would be replace as the address of head
				*fd_list = curr->next;
			if (curr->buf_s)
				free(curr->buf_s);
			free(curr);
			return ;
		}
		prev = curr; // node curr is not the desired node for deleteing, so save it in another node and go to the next node 
		curr = curr->next;
	}
}

void	free_all_list_handler(t_fd *fd_list)
{
	t_fd	*curr;
	t_fd	*next;

	curr = fd_list;
	while (curr)
	{
		next = curr->next;
		if (curr->buf_s)
			free(curr->buf_s);
		free(curr);
		curr = next;
	}
}

static t_fd	*find_the_node_helper(t_fd **fd_list, int fd)
{
	t_fd	*node;

	node = *fd_list; //we assign it to another variable because we always need the head of the list
	while (node) // we find the node or reach at the end which means that this fd reads first time
	{
		if (node->fd == fd)
			break ;
		if (node->next == NULL)
			break ; //end node
		node = node->next;
	}
	if (node->fd != fd) // means we reached at the end so we create a node and add it at the end of list
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

static char	*line_reading_handler(t_fd **node,char *buf, int fd,t_fd **fd_list)
{
	char	*line;
	char	*temp;
	int		sz;
	char	*temp_s;

	while (!is_newline_exist((*node)->buf_s))
	{
		sz = read(fd, buf, BUFFER_SIZE);
		if (sz <= 0)
		{
			if ((*node)->buf_s && *(*node)->buf_s)
				break ;
			delete_fd_node(fd_list,fd);
			return (NULL);
		}
		buf[sz] = '\0';
		temp_s = join_helper((*node)->buf_s, buf);
		if (!temp_s)
		{
				(*node)->buf_s = NULL;
				delete_fd_node(fd_list, fd);
				return (NULL);
		}
		(*node)->buf_s = temp_s;
	}
	if (!(*node)->buf_s || (*node)->buf_s[0] == '\0')
	{
		delete_fd_node(fd_list, fd);
		return (NULL);
	}
	line = extract_line_handler((*node)->buf_s);
	if (!line)
	{
		delete_fd_node(fd_list, fd);
		return (NULL);
	}
	temp = remove_extra_space_handler((*node)->buf_s);
	if (!temp)
	{
		free(line);
		delete_fd_node(fd_list, fd);	
		return (NULL);
	}
	free((*node)->buf_s);
	(*node)->buf_s = temp;
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
	{
		free(buf);
		return (NULL);
	}
	node = find_the_node_helper(&fd_list , fd);
	if (!node)
	{
		free(buf);
		//free_all_list_handler(fd_list);
		//fd_list = NULL;
		return (NULL);
	}
	line = line_reading_handler(&node, buf, fd, &fd_list);
	free(buf);
	if (line && *line != '\0')
		return (line);
	else
		return (NULL);
}
