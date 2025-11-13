/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:03:12 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/10 16:55:55 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
    char *buf;
	static char *buf_s;
	char *new;
    char *line;
    char *temp;
    int sz;
	
    sz = 1;
    if (!buf_s)
        buf_s = NULL;
    if (fd < 0 && BUFFER_SIZE <= 0)
        return (NULL);
    buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if(!buf)
        return (NULL);
    while(!is_newline_exist(buf_s) && sz >0)
    {
        sz = read_handler(fd,buf, BUFFER_SIZE);
        if ( sz < 0)
        {
            free(buf);
            free(buf_s);
            buf_s = NULL;
            return (NULL);
        }
		buf_s = join_helper(buf_s, buf);
        if(!buf_s)
        {
            free(buf);
            return (NULL);
        }
    }
    if (!buf_s || *buf_s == '\0')
    {
        free(buf_s);
        buf_s = NULL;
        return (NULL);
    }
	line = extract_line_handler(buf_s);
	temp = remove_extra_space_handler(buf_s);
	free(buf_s);
	buf_s = temp;
    free(buf);
    if (line && *line != '\0')
        return (line);
    else
        return (NULL);
}

