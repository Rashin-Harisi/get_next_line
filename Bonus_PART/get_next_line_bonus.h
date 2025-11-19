/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:43:46 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/19 13:18:31 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd
{
	int			fd;
	char		*buf_s;
	struct s_fd	*next;
}	t_fd;

char	*get_next_line(int fd);
int		merge_newline_strlen(char *s, int flag);
char	*join_helper(char *buf_s, char *buf);
char	*remove_extra_space_handler(char *buf);
char	*extract_line_handler(char *buf_s);
char	*cleanup_handler(int flag, t_fd **fd_list, int fd, void *buf_s);
void	delete_fd_node(t_fd **fd_list, int fd);

#endif
