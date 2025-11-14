#include "get_next_line_bonus.h"
#include "get_next_line.h"


char *get_next_line(int fd)
{
	static t_fd *fd_list;
	t_fd *node;
	char *buf;
	char *line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
        create_first_node(&fd_list, fd);
	node = find_the_node_helper(&fd_list , fd);
	if (!node)
	{
		free(buf);
		return (NULL);
	}
	line = line_reading_handler(&node, buf, fd, &fd_list);
	free(buf);
	if (line && *line != '\0')
		return (line);
	else
		return (NULL);
}
