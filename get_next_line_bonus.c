/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:46:25 by bbrahim           #+#    #+#             */
/*   Updated: 2021/12/03 21:10:39 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"get_next_line_bonus.h"

char	*ft_read_line(int fd, char *str)
{
	int		r;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	if (str == NULL)
		str = ft_strdup("");
	r = 1;
	while ((r != 0) && (ft_strchr(str, '\n') == NULL))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r < 0)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[r] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	if (ft_strlen(str) == 0)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*ft_line_update(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (tmp == NULL)
		return (NULL);
	j = 0;
	while (str[i] != '\0')
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*result[1024];
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result[fd] = ft_read_line(fd, result[fd]);
	if (result[fd] == NULL)
		return (NULL);
	l = ft_get_line(result[fd]);
	result[fd] = ft_line_update(result[fd]);
	return (l);
}
