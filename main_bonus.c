/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:30:28 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/14 13:31:56 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2;
    char *line;

    // Open two test files
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("open");
        return 1;
    }

    printf("Reading alternately from two files:\n\n");

    while (1)
    {
        line = get_next_line(fd1);
        if (line)
        {
            printf("FD1: %s", line);
            free(line);
        }

        line = get_next_line(fd2);
        if (line)
        {
            printf("FD2: %s", line);
            free(line);
        }

        if (!line && !get_next_line(fd1)) // both finished
            break;
    }

    close(fd1);
    close(fd2);

    printf("\nReading from standard input (stdin):\n");
    printf("Type something and press Enter. Ctrl+D to end.\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You typed: %s", line);
        free(line);
    }

    return 0;
}


