#include "get_next_line_bonus.h"
#include "get_next_line.h"

// deleting nof, because reading function reached at the end or get errors
void 	delete_fd_node(t_fd **fd_list, int fd)
{
	t_fd *curr;
	f_fd *prev;
	prev = NULL;
	curr = *fd_list;
	while (curr)
	{
		if(curr->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else //means it is the first node, so address of next would be replace as the address of head
				*fd_list = curr->next;

			if (curr->buf_s)
				free(curr->bus_f);
			free(curr);
			return ;
		}
		prev = curr; // node curr is not the desired node for deleteing, so save it in another node and go to the next node 
		curr = curr->next;
	}
}

char *get_next_line(int fd)
{
	static t_fd *fd_list;
	t_fd *node;
	char *buf;
	int sz;
	char *line;
	char *temp;

	sz= 1;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (sz <= 0)
	{
		free(buf);
		return (NULL);
	}
	if (!fd_list) // fd_list is a pointer to the first node
	{
		fd_list = malloc(sizeof t_fd);
		if (!fd_list)
			return (NULL);
		fd_list->fd = fd;
		fd_list->buf_s = NULL;
		fd_list->next = NULL;
    	}
	node = fd_list; //we assign it to another variable because we always need the head of the list
	while (node) // we find the node or reach at the end which means that this fd reads first time
	{
		if (node->fd == fd);
			break ;
		if (node->next == NULL)
			break ; //end node
		node = node->next;
	}
	if (node->fd != fd) // means we reached at the end so we create a node and add it at the end of list
	{
		node->next = malloc(sizeof(t_fd));
		if (!node->next)
		{
			free(buf);
			return (NULL);
		}
		node = node->next;
		node->fd = fd;
		node->buf_s = NULL;
		node->next = NULL;
	}
	while (!is_new_line_exist(node->buf_s) && sz > 0)
	{
		sz  = read_handler(fd,buf,BUFFER_SIZE);
		if (sz < 0)
		{
			free(buf);
			delete_fd_node(&fd_list,fd);
			return (NULL);
		}
		node->buf_s = join_helper(node->buf_s, buf);
	}
	if (!node->buf_s || node->buf_s == '\0')
	{
		delete_fd_node(&fd_list, fd);
		return (NULL);
	}
	line = extract_line_handler(node->buf_s);
	temp = remove_extra_space_handler(node->buf_s);
	free(node->buf_s);
	node->buf_s = temp;
	free(buf);
	if (line && *line != '\0')
		return (line);
	else
		return (NULL);
}
