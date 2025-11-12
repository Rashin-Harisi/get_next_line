/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:02 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/11 17:11:52 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	char *new;
	int i = 1;

	fd = open("text.txt", O_RDONLY);
	printf("open the fd = %d \n",fd);
	if (fd == -1)
		printf("Error ecoured");
	while( (new = get_next_line(fd)) != NULL)
	{
		printf("line %d : %s\n", i , new);
		free(new);
		i++;
	}	
	close(fd);
	printf("close the fd.\n");
	return (0);
}
