/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:19:35 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/09 11:47:13 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

char	*ft_join(char *buff_stat, char *buff)
{
	char	*tmp;
	int		i;

	i = 0;
	if (buff_stat == NULL)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(buff) + 1));
		if (tmp == NULL)
			return (NULL);
		while (buff[i])
		{
			tmp[i] = buff[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	tmp = ft_strjoin(buff_stat, buff);
	if (tmp == NULL)
		return (NULL);
	free (buff_stat);
	buff_stat = NULL;
	return (tmp);
}

char	*ft_fill(char *buff, char *buff_stat, int fd)
{
	int		f;

	f = 1;
	while (f > 0)
	{
		f = read(fd, buff, BUFFER_SIZE);
		if (f < 0)
			return (NULL);
		if (f == 0)
			break ;
		buff[f] = '\0';
		buff_stat = ft_join(buff_stat, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	return (buff_stat);
}

char	*ft_copy(char *buff_stat)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (buff_stat == NULL || buff_stat[0] == '\0')
		return (NULL);
	j = f_strlen(buff_stat);
	str = ft_calloc(j + 1, sizeof(char));
	while (i < j && buff_stat[i] != '\0')
	{
		str[i] = buff_stat[i];
		i++;
	}
	return (str);
}

char	*ft_cut(char *buff_stat)
{
	char	*tmp;
	int		c;
	int		i;

	if (buff_stat == NULL)
		return (NULL);
	c = f_strlen(buff_stat);
	if (buff_stat[c] == '\0')
	{
		free(buff_stat);
		buff_stat = NULL;
		return (NULL);
	}
	i = c;
	while (buff_stat[i] != '\0')
		i++;
	tmp = ft_calloc(i - c + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (buff_stat[c] != '\0')
		tmp[i++] = buff_stat[c++];
	free (buff_stat);
	buff_stat = NULL;
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*buff;
	static char	*buff_stat;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (buff_stat != NULL)
		{
			free(buff_stat);
			buff_stat = NULL;
		}
		return (NULL);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buff == NULL)
		return (NULL);
	if (ft_strchr(buff_stat, '\n') == NULL)
		buff_stat = ft_fill(buff, buff_stat, fd);
	free (buff);
	buff = NULL;
	str = ft_copy(buff_stat);
	buff_stat = ft_cut(buff_stat);
	return (str);
}
