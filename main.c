/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:02 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/10 19:05:31 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

int main()
{
	int fd;
	char *buf;
	int sz;

	buf = malloc(100 * sizeof(char));
	fd = open("text.txt", O_RDONLY);
	printf("open the fd = %d \n",fd);
	if (fd == -1)
	{
		printf("Error Number %d\n",errno);
		perror("Program");
	}
	sz = read(fd, buf, 15);
	buf[sz] = '\0';
	if (sz == 15)
	{
		printf("15 bytes are : %s\n",buf);
	}
	if (close(fd) < 0)
	{
		perror("c1");
		exit(1);
	}
	printf("close the fd.\n");
	free(buf);
	return (0);
}
