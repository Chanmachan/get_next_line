//
// Created by 本間優之介 on 2022/06/20.
//

#include "get_next_line.h"

char	*read_line(char *str, int fd)
{
	char	*buf;
	int 	rd_bytes;

	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	rd_bytes = 1;
	while (rd_bytes != 0)
	{
		//readで.txt読み込み
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char *str;
	char		*rtn_str;

	//strにread_line関数を作って読み込む
	str = read_line(str, fd);
	//strの中身をrtn_strにうつす
	rtn_str = ft_strdup(str);
	return (rtn_str);
}

#include <fcntl.h>//open
#include <stdio.h>

int main(void)
{
	char 	*str;
	int 	fd;
	size_t 	i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 6)
	{
		str = get_next_line(fd);
		printf("[%zu] : %s\n", i, str);
		i++;
	}
	close(fd);
	return (0);
}