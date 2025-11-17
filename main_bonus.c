/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:30:28 by rabdolho          #+#    #+#             */
/*   Updated: 2025/11/17 12:37:14 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

// Function to free all remaining nodes in fd_list
void free_fd_list(t_fd **fd_list)
{
    t_fd *curr = *fd_list;
    t_fd *next;

    while (curr)
    {
        next = curr->next;
        if (curr->buf_s)
            free(curr->buf_s);
        free(curr);
        curr = next;
    }
    *fd_list = NULL;
}

int main(void)
{
    int fd1, fd2;
    char *line1;
    char *line2;
    char *line3;
    int fd1_done = 0;
    int fd2_done = 0;

    // Open two test files
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("open");
        return 1;
    }

    printf("Reading alternately from two files:\n\n");

    // Loop until both files are done
    while (!fd1_done || !fd2_done)
    {
        if (!fd1_done)
        {
            line1 = get_next_line(fd1);
            if (line1)
            {
                printf("FD1: %s", line1);
                free(line1);
            }
            else
                fd1_done = 1;
        }

        if (!fd2_done)
        {
            line2 = get_next_line(fd2);
            if (line2)
            {
                printf("FD2: %s", line2);
                free(line2);
            }
            else
                fd2_done = 1;
        }
    }

    close(fd1);
    close(fd2);

    printf("\nReading from standard input (stdin):\n");
    printf("Type something and press Enter. Ctrl+D to end.\n");

    // Read from stdin until EOF
    while ((line3 = get_next_line(0)) != NULL)
    {
        printf("You typed: %s", line3);
        free(line3);
   }

    //Free any remaining nodes in fd_list
    //extern t_fd *fd_list; // make sure this matches your static fd_list in GNL
   //free_fd_list(&fd_list);

    return 0;
}

