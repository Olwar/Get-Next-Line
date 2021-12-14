#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

void	test_function(fd)
{
	int	ret;
	char buf[BUF_SIZE + 1];
	while (ret = read(fd, buf, BUF_SIZE))
	{
		if (buf[ret] == '\n')
			break;
		printf("%d\n", ret);
	}
}

int main(void)
{
	int fd;

	fd = open("todo.txt", O_RDONLY);
	test_function(fd);
}