//
// Created by 本間優之介 on 2022/06/20.
//

#include "get_next_line.h"

char	*read_lines(char *str, int fd)
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

char	*get_one_line(char *str)
{
	size_t 	i;
	char	*rtn_str;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	rtn_str = (char *) malloc(sizeof(char) * (i + 1));
	if (rtn_str == NULL)
		return (NULL);
	ft_strlcpy(rtn_str, str, i + 1);
	return (rtn_str);
}

char	*delete_last_line(char *str)
{
	size_t 	i;
	size_t 	len_new_str;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	str = str + i;
	len_new_str = ft_strlen(str);
	new_str = (char *) malloc(sizeof(char) * (len_new_str + 1));
	if (new_str == NULL)
		return (new_str);
	ft_strlcpy(new_str, str, len_new_str + 1);
	str = str - i;
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char *str;
	char		*rtn_str;

	//strにread_line関数を作って読み込む
	str = read_lines(str, fd);
	if (str == NULL)
		return (NULL);
	//strの一行目をrtn_strにうつす
	rtn_str = get_one_line(str);
	//もういらない部分を取り除く
	str = delete_last_line(str);
	return (rtn_str);
}


/*#include <fcntl.h>//open
#include <stdio.h>

int main(void)
{
	char 	*str;
	int 	fd;
	size_t 	i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 4)
	{
		str = get_next_line(fd);
		printf("[%zu] : %s\n-------------\n", i, str);
		i++;
	}
	close(fd);
	return (0);
}*/
