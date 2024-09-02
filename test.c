#include "get_next_line.h"
#include <stdio.h>

void	test_get_next_line(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
}

void	test_with_buffer_size(int fd, int buffer_size)
{
	printf("Testing with BUFFER_SIZE = %d\n", buffer_size);
#undef BUFFER_SIZE
#define BUFFER_SIZE buffer_size
	test_get_next_line(fd);
	lseek(fd, 0, SEEK_SET); // Reset file descriptor for next test
}

int	main(void)
{
	int fd;

	// Test with a file
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file", 19);
		return (1);
	}

	// Large BUFFER_SIZE (>1024)
	test_with_buffer_size(fd, 2048);

	// Small BUFFER_SIZE (< 8, and 1)
	test_with_buffer_size(fd, 1);
	test_with_buffer_size(fd, 4);

	// BUFFER_SIZE exactly the length of the line to read
	test_with_buffer_size(fd, 10); // Assuming a line of 10 characters

	// 1 byte variant (+/-) between the line and the BUFFER_SIZE
	test_with_buffer_size(fd, 9);
	test_with_buffer_size(fd, 11);

	close(fd);

	// Test reading from stdin
	printf("Testing with stdin (type some lines and press Ctrl+D to end):\n");
	test_get_next_line(STDIN_FILENO);

	return (0);
}