#include "get_next_line_bonus.h"
#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_fd *fd_list;
    char *buf;

    buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buf)
        return (NULL);
    buf = read_handler(fd,buf,BUFFER_SIZE);
    fd_list = NULL; // the head for the first node
    while (fd_list->next != NULL)
    {
        if(fd_list->fd != fd)
        {
            fd_list->fd == fd;
            fd_list->buf_s = buf;
            fd_list->next = NULL;
        }
    }
}