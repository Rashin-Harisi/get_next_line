/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:43:46 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/18 11:43:54 by rabdolho         ###   ########.fr       */
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
int		is_newline_exist(char *buf);
int		ft_strlen(char *str);
char	*join_helper(char *buf_s, char *buf);
char	*remove_extra_space_handler(char *buf);
char	*extract_line_handler(char *buf_s);

#endif
