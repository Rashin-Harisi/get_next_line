/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:03:49 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/10 17:02:05 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
int	read_handler(int fd,char *buf, int n);
int	is_newline_exist(char *buf);
int	ft_strlen(char *str);
char	*join_helper(char *buf_s, char *buf);
char	*remove_extra_space_handler(char *buf);
char *extract_line_handler(char *buf_s);

#endif
