#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_fd
{
    int fd;
    char *buf_s;
    struct s_fd *next;
} t_fd;

char	*get_next_line(int fd);
void create_first_node(t_fd **fd_list, int fd);
void    delete_fd_node(t_fd **fd_list, int fd);
t_fd	*find_the_node_helper(t_fd **fd_list, int fd);
char *line_reading_handler(t_fd **node,char *buf, int fd,t_fd **fd_list);


#endif
