//
// Created by 本間優之介 on 2022/06/20.
//

#include "get_next_line.h"

char	*read_lines(char *str, int fd)
{
	char	*buf;
	ssize_t 	rd_bytes;
	 //ssize_t return
	char 	*tmp;

	rd_bytes = 1;
	while (rd_bytes != 0 && !ft_strchr(str, '\n'))
	{
		buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (NULL);
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		free(buf);
	}
	return (str);
}
//char *tmp = &str
//joinした後のstrと前のstrは違うからfree注意

char	*get_one_line(char *str)
{
	size_t 	i;
	char	*rtn_str;

	if (str[0] == '\0')
	{
		return (NULL);
	}
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	rtn_str = ft_substr(str, 0, i + 1);
	if (rtn_str == NULL)
	{
		free(str);
		return (NULL);
	}
	return (rtn_str);
}

char	*delete_last_line(char *str)
{
	size_t 	i;
	char	*new_str;

	if (str == NULL || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		return (NULL);
	}
	new_str = ft_substr(str, i + 1, ft_strlen(str));
	if (new_str == NULL)
	{
		return (NULL);
	}
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char *str;
	char		*rtn_str;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	//strにread_line関数を作って読み込む
	str = read_lines(str, fd);
	if (!str)
	{
		return (NULL);
	}
	//strの一行目をrtn_strにうつす
	rtn_str = get_one_line(str);
	//もういらない部分を取り除く
	str = delete_last_line(str);
	return (rtn_str);
}



/*#include <fcntl.h>//open
#include <stdio.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}
int main(void)
{
	char 	*str;
	int 	fd;
	size_t 	i;

	i = 0;
	fd = open("text00.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("str : [%s]\n", str);
		printf("%p\n", str);
		if (str == NULL)
			break;
		free(str);
		i++;
	}
	close(fd);
//	system("leaks a.out");
	return (0);
}*/
//-fsanitize=address -g