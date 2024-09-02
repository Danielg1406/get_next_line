#include "get_next_line.h"
#include <fcntl.h>      
#include <unistd.h>     
#include <stdio.h>      
#include <stdlib.h>     

void test_file(const char *filename, int buffer_size)
{
    int     fd;
    char    *line;

    printf("Testing file: %s with BUFFER_SIZE: %d\n", filename, buffer_size);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Error opening file\n", 19);
        return;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    if (line == NULL)
        printf("\nNULL returned (end of file).\n");
    close(fd);
}

void test_stdin(int buffer_size)
{
    char    *line;

    printf("Testing stdin with BUFFER_SIZE: %d. Type input (or Press CTRL + D to exit):\n", buffer_size);
    while ((line = get_next_line(0)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    if (line == NULL)
        printf("\nNULL returned (end of input).\n");
}

int main(void)
{
    // Test with different BUFFER_SIZE values
    int buffer_sizes[] = {1, 42, 1024, 1000000};
    size_t i;

    // Test files for each buffer size
    for (i = 0; i < sizeof(buffer_sizes) / sizeof(int); i++)
    {
        printf("\n==============================================\n");
        printf("\nRunning tests with BUFFER_SIZE = %d\n", buffer_sizes[i]);
        printf("\n==============================================\n");

        // Test with various files
        test_file("tests/empty.txt", buffer_sizes[i]);  // Empty file
				printf("\n==============================================\n");
        test_file("tests/one_char.txt", buffer_sizes[i]);  // Single character
				printf("\n==============================================\n");
        test_file("tests/one_line_no_nl.txt", buffer_sizes[i]);  // Single line, no newline
				printf("\n==============================================\n");
        test_file("tests/only_nl.txt", buffer_sizes[i]);  // Only newline
				printf("\n==============================================\n");
        test_file("tests/multiple_nl.txt", buffer_sizes[i]);  // Multiple newlines
				printf("\n==============================================\n");
        test_file("tests/multiple_lines_short.txt", buffer_sizes[i]);  // Multiple short lines
				printf("\n==============================================\n");
        test_file("tests/giant_line.txt", buffer_sizes[i]);  // Single long line (2k+ characters)
				printf("\n==============================================\n");
        test_file("tests/multiple_lines_long.txt", buffer_sizes[i]);  // Multiple long lines (2k+ characters)
    }

    // Test reading from stdin
		 printf("\n==============================================\n");
        printf("Test reading from stdinn");
        printf("\n==============================================\n");
    test_stdin(buffer_sizes[0]); // Test reading from stdin with a small BUFFER_SIZE
    return (0);
}
