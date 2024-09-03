#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	test_invalid_fd(void)
{
	char	*line;

	printf("Testing with invalid file descriptor:\n");
	line = get_next_line(42);
	// File descriptor 42 is arbitrary and likely invalid
	if (line == NULL)
		printf("PASS: Returned NULL for invalid file descriptor.\n");
	else
	{
		printf("FAIL: Expected NULL for invalid file descriptor, got %s\n",
			line);
		free(line);
	}
}

void	test_closed_fd(void)
{
	int		fd;
	char	*line;

	printf("Testing with closed file descriptor:\n");
	fd = open("tests/one_line_no_nl.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
		return ;
	}
	close(fd); // Close the file descriptor
	line = get_next_line(fd);
	// Attempt to read from the closed descriptor
	if (line == NULL)
		printf("PASS: Returned NULL for closed file descriptor.\n");
	else
	{
		printf("FAIL: Expected NULL for closed file descriptor, got %s\n",
			line);
		free(line);
	}
}

int	main(void)
{
	// Run error management tests
	printf("\n==============================================\n");
	printf("Running error management tests\n");
	printf("==============================================\n");
	test_invalid_fd();
	test_closed_fd();
	return (0);
}