/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:02 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/17 13:06:52 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
/* testing with fd > 2
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
*/
/*
//test with fd = 0 (stdin)
int main(void)
{
    char *line;

    printf("Type something (Ctrl+D to end):\n");
    while ((line = get_next_line(0)) != NULL) // 0 = stdin
    {
        printf("You entered: %s", line);
        free(line);
    }
    return 0;
}
*/
// stdout is for writing not reading , so read() returns -1

int main(void){
	int fd = open("text.txt", O_RDONLY);
	char *line;

	printf("Reading from file:\n");
	
	while ((line = get_next_line(fd)) != NULL)	
	{
	    printf("%s", line);
	    free(line);
	}
	
	printf("\nNow type something:\n");
	while ((line = get_next_line(0)) != NULL)
	{
	    printf("stdin: %s", line);
	    free(line);
	}
	return 0;
}
