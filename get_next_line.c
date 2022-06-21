//
// Created by 本間優之介 on 2022/06/20.
//

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*str;
	size_t 	buf;

	str = (char *) malloc(sizeof(char) * (42 + 1));
	if (str == NULL)
		return (NULL);
	if (fd == 0)
	{
		buf = read(fd, str, 42); //change 42
		if (buf < 0)
			return (NULL);
		str[42] = '\0';
	}
	return (str);
	//fdごと（ファイルからか標準入力からか）に挙動変える必要あり
}

#include <stdio.h>

int main(void)
{
	char *str;

	str = get_next_line(0);
	printf("%s\n", str);
}