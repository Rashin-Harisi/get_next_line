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


#endif