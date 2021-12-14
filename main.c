#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include 

int main(void)
{
	char *s;
	int x;

	int fd = open("todo.txt", O_RDONLY);
	int fd1 = open("toinenTesti.txt", O_RDONLY);
	int fd2 = open("test1.txt", O_RDONLY);
	int fd3 = open("test2.txt", O_RDONLY);
	int fd4 = open("empty.txt", O_RDONLY);
	int fd5 = open("emptyline.txt", O_RDONLY);
	int fd6 = open("bible.txt", O_RDONLY);
	

	printf("-------\nTesting negative, supposed -1, fd:\n%d\n", get_next_line(-5, &s));
	printf("-------\nTesting NULL, supposed -1, **line:\n%d\n", get_next_line(1, 0));
	printf("-------\nBasic tests, sisalto 1:na ja 0 kun ei uutta linea:\n");

	for (int i = 0; i < 2; i++)
	{
		x = get_next_line(fd, &s);
		printf("%d, %s\n", x, s);
	}
	printf("\n");



	while (1)
	{
		x = get_next_line(fd1, &s);
		
		printf("%d, %s\n", x, s);
		if (x <= 0)
			break ;
	}

	printf("-------\nTesting empty file, supposed 0,:\n");
	x = get_next_line(fd4, &s);
	printf("%d, %s\n", x, s);

	printf("-------\nTesting file with just empty line, supposed 1 ja sit 0:\n");
	x = get_next_line(fd5, &s);
	printf("%d, %s\n", x, s);
	x = get_next_line(fd5, &s);
	printf("%d, %s\n", x, s);	

	printf("-------\nTesting calling diff fd one after another:\n");
	get_next_line(fd2, &s);
	printf("supposed first call, %s\n",s);
	get_next_line(fd3, &s);
	printf("second call, %s\n",s);
	get_next_line(fd2, &s);
	printf("third call, %s\n",s);
	get_next_line(fd3, &s);
	printf("fourth call, %s\n",s);

	printf("-------\nBIBLE:\n-----------");
	int i = 0;
	while (1)
	{
		x = get_next_line(fd6, &s);
		
		printf("%d, %s\n", i, s);
		if (x <= 0)
			break ;
		i++;
	}

	printf("-------\nTesting stdin:\n");
	while (1)
	{
		get_next_line(1, &s);
		printf("%s\n",s);
	}



}