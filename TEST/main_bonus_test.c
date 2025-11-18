#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

#define TEST_FILE_COUNT 11

// List of all files used by francinette
char *test_files[] = {
    "1char.txt",
    "empty.txt",
    "giant_line.txt",
    "giant_line_nl.txt",
    "lines_around_10.txt",
    "multiple_nl.txt",
    "one_line_no_nl.txt",
    "only_nl.txt",
    "read_error.txt",
    "variable_nls.txt",
    "multiple_fds.txt"        // add your own file for multi-FD tests
};

int buffer_sizes[] = {1, 10, 1000000};

void test_file(char *filename)
{
    printf("\n=== Testing file: %s ===\n", filename);

    for (int b = 0; b < 3; b++)
    {
        int bs = buffer_sizes[b];
        printf("\n-- BUFFER_SIZE = %d --\n", bs);

        int fd = open(filename, O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            continue;
        }

        char *line;
        int line_num = 1;
        int limit = 100000;  // safety to detect infinite loops

        while (limit-- > 0)
        {
            line = get_next_line(fd);
            if (!line)
                break;

            printf("Line %d: %s", line_num++, line);
            free(line);
        }

        if (limit <= 0)
            printf("⚠️  Infinite loop detected!\n");

        close(fd);
    }
}

void test_two_fds(void)
{
    printf("\n=========== TESTING MULTIPLE FDs ==========\n");

    int fd1 = open("1char.txt", O_RDONLY);
    int fd2 = open("multiple_nl.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        printf("Cannot open multi-FD files.\n");
        return;
    }

    char *l1, *l2;
    int turn = 0;

    while (1)
    {
        if (turn % 2 == 0)
        {
            l1 = get_next_line(fd1);
            if (!l1)
                break;
            printf("FD1: %s", l1);
            free(l1);
        }
        else
        {
            l2 = get_next_line(fd2);
            if (!l2)
                break;
            printf("FD2: %s", l2);
            free(l2);
        }
        turn++;
    }

    close(fd1);
    close(fd2);
}

void test_stdin(void)
{
    printf("\n========== TESTING STDIN ==========\n");
    printf("Type something and press Enter (Ctrl+D to exit):\n");

    char *line;
    while ((line = get_next_line(0)) != NULL)
    {
        printf("STDIN: %s", line);
        free(line);
    }
}

int main(void)
{
    printf("=========== GET_NEXT_LINE BONUS TESTER ===========\n");

    // test all files with multiple BUFFER_SIZE values
    for (int i = 0; i < TEST_FILE_COUNT; i++)
        test_file(test_files[i]);

    // test reading from multiple FDs
    test_two_fds();

    // test stdin
    test_stdin();

    return 0;
}

